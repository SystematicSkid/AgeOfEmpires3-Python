#pragma once
/* Pybind includes */
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
namespace py = pybind11;

/* Initialize our real python export/module */
/* This must be placed in global scope */
PYBIND11_EMBEDDED_MODULE(communication, m)
{
	/* Documentation helper */
	m.doc() = "Python bindings for Age of Empires 3 DE";

	/* We do not need to add much else here because all of our exports will be */
	/*  added dynamically upon initialization! */
}

namespace Core::Python
{
	/* List of all loaded modules */
	std::vector<py::module_> loaded_modules;
	/* Our module */
	py::module_ communication_module;

	/* Dynamically add all exports to the embedded python instance */
	BOOL ExportSyscalls(Engine::Console* console)
	{
		if (!console)
			return FALSE;

		Engine::SyscallModule* syscall_module = console->syscall_module;
		if (!syscall_module)
			return FALSE;

		auto syscall_class = py::class_<Engine::Syscall*>(communication_module, "Syscall");

		for (int i = 0; i < syscall_module->num_syscalls; i++)
		{
			Engine::Syscall* syscall = syscall_module->syscalls[i];
			if(!syscall)
				continue;
			std::string syscall_name = syscall->GetName();
			DEBUG("[ + ] Adding Syscall %s (%i)...\n", syscall_name.c_str(), syscall->id);
			DEBUG("\tCallback: 0x%p\n", syscall->callback);
			py::object callback = py::cast(&syscall->callback);
			try
			{
				syscall_class.def_static(syscall_name.c_str(), reinterpret_cast<DWORD64(__fastcall*)(py::args)>(syscall->callback));
			}
			catch (const std::exception& e)
			{
				DEBUG("[ ! ] Failed to add %s!\n\t%s\n", syscall_name.c_str(), e.what());
			}
		}

		return TRUE;
	}

	/* Initialization method */
	BOOL Initialize( VOID )
	{
		/* Create our embedded interpreter */
		py::initialize_interpreter( );
		/* Import embedded module */
		communication_module = py::module_::import("communication");

		/* Execute test string */
		py::exec("print('Hello from embedded Python interpreter!')");

		/* Dynamically export syscalls */
		if (!Python::ExportSyscalls(Engine::Console::Instance))
			return FALSE;

		return TRUE;
	}

	/* Finalize */
	BOOL Finalize( VOID )
	{
		/* Destruct our embedded interpreter */
		py::finalize_interpreter( );
	}
}