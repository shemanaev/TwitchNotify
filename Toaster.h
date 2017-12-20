#pragma once

#include <Windows.h>

typedef int(*IsToastsSupportedFunc)(void);
typedef void(*ShowToastNotificationFunc)(LPCWSTR channel, LPCWSTR status, LPCWSTR game, LPCWSTR image, int expiration);
typedef void(*ToastCallbackFunc)(LPCWSTR channel, int action);
typedef void(*SetHandlerFunc)(ToastCallbackFunc handler);
