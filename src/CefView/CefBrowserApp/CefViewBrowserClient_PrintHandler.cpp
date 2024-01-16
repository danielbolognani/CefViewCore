#include <CefViewBrowserClient.h>

#pragma region std_headers
#include <sstream>
#include <string>
#include <algorithm>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

#include <Common/CefViewCoreLog.h>

CefRefPtr<CefPrintHandler>
CefViewBrowserClient::GetPrintHandler()
{
  return this;
}

void
CefViewBrowserClient::OnPrintStart(CefRefPtr<CefBrowser> browser)
{
  CEF_REQUIRE_UI_THREAD();
  auto delegate = client_delegate_.lock();
  if (delegate)
    delegate->printStart(browser);
}

void
CefViewBrowserClient::OnPrintSettings(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefPrintSettings> settings,
                                      bool get_defaults)
{
  CEF_REQUIRE_UI_THREAD();
  auto delegate = client_delegate_.lock();
  if (delegate)
    delegate->printSettings(browser, settings, get_defaults);
}

bool
CefViewBrowserClient::OnPrintDialog(CefRefPtr<CefBrowser> browser,
                                    bool has_selection,
                                    CefRefPtr<CefPrintDialogCallback> callback)
{
  CEF_REQUIRE_UI_THREAD();
  auto delegate = client_delegate_.lock();
  if (delegate)
    return delegate->printDialog(browser, has_selection, callback);

  return false;
}

bool
CefViewBrowserClient::OnPrintJob(CefRefPtr<CefBrowser> browser,
                                 const CefString& document_name,
                                 const CefString& pdf_file_path,
                                 CefRefPtr<CefPrintJobCallback> callback)
{
  CEF_REQUIRE_UI_THREAD();
  auto delegate = client_delegate_.lock();
  if (delegate)
    return delegate->printJob(browser, document_name, pdf_file_path, callback);

  return false;
}

void
CefViewBrowserClient::OnPrintReset(CefRefPtr<CefBrowser> browser)
{
  CEF_REQUIRE_UI_THREAD();
  auto delegate = client_delegate_.lock();
  if (delegate)
    delegate->printReset(browser);
}
