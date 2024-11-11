#include <ntddk.h>
#include <wdm.h>

void SampleUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Sample Driver Unload called"));
}

extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath);

	DriverObject->DriverUnload = SampleUnload;

	KdPrint(("Sample Driver initialized successfully"));
	OSVERSIONINFOW l;
	l.dwOSVersionInfoSize = 276;
	NTSTATUS status = RtlGetVersion(&l);

	if (NT_SUCCESS(status)) {
		KdPrint(("The version is: %u.%u\nThe build is %u", l.dwMajorVersion, l.dwMinorVersion, l.dwBuildNumber));
	}
	else {
		KdPrint(("Error"));
	}

	return STATUS_SUCCESS;
}