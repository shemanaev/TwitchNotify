#include "stdafx.h"

using namespace WinToastLib;

ToastCallbackFunc gHandler = nullptr;

class ToastHandler : public IWinToastHandler {
public:
	ToastHandler(std::wstring channel, ToastCallbackFunc handler): _channel(channel), _handler(handler) {}

	void toastActivated() const {
	}

	void toastActivated(int actionIndex) const {
		_handler(_channel.c_str(), actionIndex);
	}

	void toastDismissed(WinToastDismissalReason state) const {
	}

	void toastFailed() const {
	}

private:
	std::wstring _channel;
	ToastCallbackFunc _handler;
};

extern "C" __declspec(dllexport) void SetHandler(ToastCallbackFunc handler)
{
	gHandler = handler;
}

extern "C" __declspec(dllexport) int IsToastsSupported()
{
	return WinToast::isCompatible();
}

extern "C" __declspec(dllexport) void ShowToastNotification(LPCWSTR channel, LPCWSTR status, LPCWSTR game, LPCWSTR image, int expiration)
{
	if (!WinToast::isCompatible()) {
		return;
	}

	std::wstring appName = L"TwitchNotify";

	WinToast::instance()->setAppName(appName);
	WinToast::instance()->setAppUserModelId(appName);

	if (!WinToast::instance()->initialize()) {
		return;
	}

	WinToastTemplate templ(WinToastTemplate::ImageAndText04);
	templ.setImagePath(image);
	templ.setTextField(channel, WinToastTemplate::FirstLine);
	templ.setTextField(status, WinToastTemplate::SecondLine);
	templ.setTextField(game, WinToastTemplate::ThirdLine);
	templ.setExpiration(expiration * 1000);
	// templ.setAudio(true);


	templ.addAction(L"Player");
	templ.addAction(L"Browser");

	WinToast::instance()->showToast(templ, new ToastHandler(channel, gHandler));
}
