#include <Windows.h>
#include <string>
#include <sstream>

// глобальные переменные
HINSTANCE hInst;
HWND hButton;
HWND hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6, hEdit7;
HWND hStatic1, hStatic2, hStatic3, hStatic4, hStatic5, hStatic6, hStatic7;
double currentRatio, availabilityOfOwnWorkingCapital, securityRatioOfLiabilities;
std::string resultText;

// прототипы функций
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateControls(HWND);

// точка входа
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    hInst = hInstance;

    // регистрация класса окна
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"BankruptcyCalculator";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    // создание окна
    HWND hWnd = CreateWindow(
        L"BankruptcyCalculator",
        L"Bankruptcy Calculator",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    CreateControls(hWnd);

    // отображение окна
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // цикл сообщений
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// обработчик сообщений окна
// обработчик сообщений окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        if ((HWND)lParam == hButton)
        {
            // получение значений из текстовых полей
            char szCurrentAssets[20];
            char szCurrentLiabilities[20];
            char zsEquityCapital[20];
            char szLongTermLiabilities[20];
            char szLongTermAssets[20];
            char szBalanceSheetSummary[20];

            GetWindowTextA(hEdit1, szCurrentAssets, 20);
            GetWindowTextA(hEdit2, szCurrentLiabilities, 20);
            GetWindowTextA(hEdit3, zsEquityCapital, 20);
            GetWindowTextA(hEdit4, szLongTermLiabilities, 20);
            GetWindowTextA(hEdit5, szLongTermAssets, 20);
            GetWindowTextA(hEdit6, szBalanceSheetSummary, 20);

            // расчет показателей банкротства
            double currentAssets = atof(szCurrentAssets);
            double currentLiabilities = atof(szCurrentLiabilities);
            double equityCapital = atof(zsEquityCapital);
            double longTermLiabilities = atof(szLongTermLiabilities);
            double longTermAssets = atof(szLongTermAssets);
            double balanceSheetSummary = atof(szBalanceSheetSummary);

            currentRatio = currentAssets / currentLiabilities;
            availabilityOfOwnWorkingCapital = (equityCapital + longTermLiabilities - longTermAssets) / currentAssets;
            securityRatioOfLiabilities = (currentLiabilities + longTermLiabilities) / balanceSheetSummary;

            // формирование текста результата
            std::ostringstream stream;
            stream << "Коэффициент текущей ликвидности: " << currentRatio << std::endl;
            stream << "Коэффициент обеспеченности собственными оборотными средствами: " << availabilityOfOwnWorkingCapital << std::endl;
            stream << "Коэффициент обеспеченности обязательств активами: " << securityRatioOfLiabilities << std::endl;
            resultText = stream.str();

            // вывод результата в текстовое поле
            SetWindowTextA(hEdit7, resultText.c_str());
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
// создание элементов управления
// создание элементов управления
void CreateControls(HWND hWnd)
{
    hStatic1 = CreateWindow(
        L"STATIC",
        L"Краткосрочные активы:",
        WS_VISIBLE | WS_CHILD,
        20, 20, 200, 20,
        hWnd, NULL, hInst, NULL);
    hEdit1 = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        220, 20, 200, 20,
        hWnd, NULL, hInst, NULL);

    hStatic2 = CreateWindow(
        L"STATIC",
        L"Краткосрочные об-ва:",
        WS_VISIBLE | WS_CHILD,
        20, 60, 200, 20,
        hWnd, NULL, hInst, NULL);

    hEdit2 = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        220, 60, 200, 20,
        hWnd, NULL, hInst, NULL);

    hStatic3 = CreateWindow(
        L"STATIC",
        L"Собственный капитал:",
        WS_VISIBLE | WS_CHILD,
        20, 100, 200, 20,
        hWnd, NULL, hInst, NULL);

    hEdit3 = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        220, 100, 200, 20,
        hWnd, NULL, hInst, NULL);

    hStatic4 = CreateWindow(
        L"STATIC",
        L"Долгосрочные об-ва:",
        WS_VISIBLE | WS_CHILD,
        20, 140, 200, 20,
        hWnd, NULL, hInst, NULL);

    hEdit4 = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        220, 140, 200, 20,
        hWnd, NULL, hInst, NULL);

    hStatic5 = CreateWindow(
        L"STATIC",
        L"Долгосрочные активы:",
        WS_VISIBLE | WS_CHILD,
        20, 180, 200, 20,
        hWnd, NULL, hInst, NULL);

    hEdit5 = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        220, 180, 200, 20,
        hWnd, NULL, hInst, NULL);

    hStatic6 = CreateWindow(
        L"STATIC",
        L"Итог бух. баланса:",
        WS_VISIBLE | WS_CHILD,
        20, 220, 200, 20,
        hWnd, NULL, hInst, NULL);

    hEdit6 = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        220, 220, 200, 20,
        hWnd, NULL, hInst, NULL);

    hButton = CreateWindow(
        L"BUTTON",
        L"Рассчитать",
        WS_VISIBLE | WS_CHILD,
        20, 260, 400, 30,
        hWnd, NULL, hInst, NULL);

    hStatic7 = CreateWindow(
        L"STATIC",
        L"Результат:",
        WS_VISIBLE | WS_CHILD,
        20, 300, 200, 20,
        hWnd, NULL, hInst, NULL);

    hEdit7 = CreateWindow(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_READONLY,
        20, 300, 400, 200,
        hWnd, NULL, hInst, NULL);
}

// функция для получения значения из текстового поля
double GetDoubleFromEdit(HWND hEdit)
{
    int len = GetWindowTextLength(hEdit);
    if (len == 0) {
        return 0.0;
    }
    std::wstring text(len + 1, L'\0');
    GetWindowText(hEdit, &text[0], len + 1);
    try {
        return std::stod(text);
    }
    catch (std::invalid_argument&) {
        return 0.0;
    }
}

// функция для вывода сообщения об ошибке
void ShowErrorMessage(HWND hWnd, LPCWSTR message)
{
    MessageBox(hWnd, message, L"Ошибка", MB_OK | MB_ICONERROR);
}