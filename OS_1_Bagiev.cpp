//
// Created by arsla on 03.10.2021.
//

#include <iostream>
#include "windows.h"

using namespace std;

void PrintMenu();
void PrintMenuAttributes();
void DisplayingAListOfDisks();
void DiscInformation();
void CreatingDirectories();
void CreationInTheSpecifiedDirectory();
void CopAndMovFiles();
void AnalAndModFile();
void FileAttributesGet();
void FileAttributesChange();
void FileInformationByHandle();
void FileTimeGet();
void FileTimeSet();

int main() {
    system("chip 1251");
    setlocale(LC_ALL, "Russian");

    int menu;

    // ОСНОВНОЙ КОД
    do {
        system("cls");
        PrintMenu();

        cin >> menu;
        system("cls");

        switch (menu) {
        case 1: // Первый пункт - вывод списка дисков
            
            DisplayingAListOfDisks();

            break;
        
        case 2: // Второй пункт - вывод информации о диске

            DiscInformation();
            break;

        case 3: // Третий пункт - создание и удаление заданных каталогов

            CreatingDirectories();
            break;
        
        case 4: // Четвертый пункт - создание в указанном каталоге

            CreationInTheSpecifiedDirectory();
            break;

        case 5: // Пятый пункт - копирование и перемещение файлов 

            CopAndMovFiles();
            break;

        case 6: // Шестой пункт - анализ и изменение атрибутов файлов

            AnalAndModFile();
            break;
        }
        
        
    } while (menu != 0);

    return(0);
}

// Вывод общего меню
void PrintMenu() {
    cout << "+---+------------------------------------------------------------+" << '\n';
    cout << "| 1 | вывод списка дисков                                        |" << '\n';
    cout << "+---+------------------------------------------------------------+" << '\n';
    cout << "| 2 | вывод информации о диске и размер свободного пространства  |" << '\n';
    cout << "+---+------------------------------------------------------------+" << '\n';
    cout << "| 3 | создание и удаление заданных каталогов                     |" << '\n';
    cout << "+---+------------------------------------------------------------+" << '\n';
    cout << "| 4 | создание в указанном каталоге                              |" << '\n';
    cout << "+---+------------------------------------------------------------+" << '\n';
    cout << "| 5 | копирование и перемещение файлов между каталогами          |" << '\n';
    cout << "+---+------------------------------------------------------------+" << '\n';
    cout << "| 6 | анализ и изменение атрибутов файлов                        |" << '\n';
    cout << "+---+------------------------------------------------------------+" << '\n';
    cout << "| 0 | Выход из программы                                         |" << '\n';
    cout << "+---+------------------------------------------------------------+" << '\n';
}

void PrintMenuAttributes() {
    cout << "+---+--------------------------------------------+" << '\n';
    cout << "| 1 | вывод информации об атрибутах              |" << '\n';
    cout << "+---+--------------------------------------------+" << '\n';
    cout << "| 2 | изменение информации об атрибутах          |" << '\n';
    cout << "+---+--------------------------------------------+" << '\n';
    cout << "| 3 | вывод информации о файле по дескриптору    |" << '\n';
    cout << "+---+--------------------------------------------+" << '\n';
    cout << "| 4 | информация о системном времени             |" << '\n';
    cout << "+---+--------------------------------------------+" << '\n';
    cout << "| 5 | изменение системного времени               |" << '\n';
    cout << "+---+--------------------------------------------+" << '\n';
    cout << "| 0 | Выход из программы                         |" << '\n';
    cout << "+---+--------------------------------------------+" << '\n';
}

// Вывод всех дисков
void DisplayingAListOfDisks() {
    int temp;
    int n;

    cout << "Список доступных дисков" << '\n';

    temp = GetLogicalDrives();

    for (int i = 0; i < 26; i++) { 
        n = ((temp >> i) & 1);
        if (n) {
            cout << "- " << (char)(65 + i) << ":\\" << '\n';
        }
    }

    system("pause");
}

// Вывод информации о диске
void DiscInformation() {
    string disk_name;
    wstring w_string;

    LPCWSTR name;
    UINT y;

    WCHAR lpVolumeNameBuffer[MAX_PATH + 1];
    DWORD lpVolumeSerialNumber = 0;
    DWORD lpMaximumComponentLength = 0;
    DWORD lpFileSystemFlags = 0;
    WCHAR lpFileSystemNameBuffer[MAX_PATH + 1];

    DWORD sectorsPerCluster;
    DWORD bytesPerSector;
    DWORD numberOfFreeClusters;
    DWORD totalNumberOfClusters;

    //GetDriveType

    cout << "Введите название диска (например: c:\\): ";
    cin >> disk_name;

    w_string = wstring(disk_name.begin(), disk_name.end());
    name = w_string.c_str();
    y = GetDriveType(name);

    if (y == DRIVE_UNKNOWN) cout << "- UNKNOWN           (Неизвестный тип)" << '\n';
    if (y == DRIVE_NO_ROOT_DIR) cout << "- DRIVE NO ROOT DIR (Неправильный путь)" << '\n';
    if (y == DRIVE_REMOVABLE) cout << "- REMOVABLE         (Съёмный диск)" << '\n';
    if (y == DRIVE_FIXED) cout << "- FIXED             (Фиксированный диск)" << '\n';
    if (y == DRIVE_REMOTE) cout << "- REMOTE            (Удалённый диск)" << '\n';
    if (y == DRIVE_CDROM) cout << "- CDROM             (CD-ROM диск)" << '\n';
    if (y == DRIVE_RAMDISK) cout << "- RAMDISK           (RAM диск)" << '\n';

    //GetVolumeInformation
    if (!GetVolumeInformation(name, lpVolumeNameBuffer, sizeof(lpVolumeNameBuffer), 
        &lpVolumeSerialNumber, &lpMaximumComponentLength, &lpFileSystemFlags, 
        lpFileSystemNameBuffer, sizeof(lpFileSystemNameBuffer)))
    {
        cout << "Ошибка. Запрос не обработан";
    }
    else {
        cout << '\n' << "Название указанного диска: " << lpVolumeNameBuffer << '\n';
        cout << "Cерийный номер диска:      " << hex << lpVolumeSerialNumber << '\n';
        cout << "Максимальная длина файла:  " << dec << lpMaximumComponentLength << '\n';
        cout << "Опции файловой системой:   " << '\n';

        //Расшифровка lpFileSystemFlags

        if (lpFileSystemFlags & FILE_CASE_PRESERVED_NAMES)
            cout << " - Указанный том поддерживает сохраненный регистр имен файлов, когда он помещает имя на диск." << '\n';
        if (lpFileSystemFlags & FILE_CASE_SENSITIVE_SEARCH)
            cout << " - Указанный том поддерживает имена файлов с учетом регистра." << '\n';
        if (lpFileSystemFlags & FILE_DAX_VOLUME)
            cout << " - Указанный том является томом прямого доступа (DAX)." << '\n';
        if (lpFileSystemFlags & FILE_FILE_COMPRESSION)
            cout << " - Указанный том поддерживает сжатие файлов." << '\n';
        if (lpFileSystemFlags & FILE_NAMED_STREAMS)
            cout << " - Указанный том поддерживает именованные потоки." << '\n';
        if (lpFileSystemFlags & FILE_PERSISTENT_ACLS)
            cout << " - Указанный том сохраняет и применяет списки управления доступом (ACL)." << '\n';
        if (lpFileSystemFlags & FILE_READ_ONLY_VOLUME)
            cout << " - Указанный том доступен только для чтения." << '\n';
        if (lpFileSystemFlags & FILE_SEQUENTIAL_WRITE_ONCE)
            cout << " - Указанный том поддерживает одну последовательную запись." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_ENCRYPTION)
            cout << " - Указанный том поддерживает зашифрованную файловую систему (EFS)." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_EXTENDED_ATTRIBUTES)
            cout << " - Указанный том поддерживает расширенные атрибуты." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_HARD_LINKS)
            cout << " - Указанный том поддерживает жесткие ссылки." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_OBJECT_IDS)
            cout << " - Указанный том поддерживает идентификаторы объектов." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_OPEN_BY_FILE_ID)
            cout << " - Файловая система поддерживает открытие по FileID." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_REPARSE_POINTS)
            cout << " - Указанный том поддерживает точки повторного разбора." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_SPARSE_FILES)
            cout << " - Указанный том поддерживает разреженные файлы." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_TRANSACTIONS)
            cout << " - Указанный том поддерживает транзакции." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_USN_JOURNAL)
            cout << " - Указанный том поддерживает журналы обновления порядковых номеров (USN)." << '\n';
        if (lpFileSystemFlags & FILE_UNICODE_ON_DISK)
            cout << " - Указанный том поддерживает Unicode в именах файлов по мере их появления на диске." << '\n';
        if (lpFileSystemFlags & FILE_VOLUME_IS_COMPRESSED)
            cout << " - Указанный том является сжатым томом." << '\n';
        if (lpFileSystemFlags & FILE_VOLUME_QUOTAS)
            cout << " - Указанный том поддерживает дисковые квоты." << '\n';
        if (lpFileSystemFlags & FILE_SUPPORTS_BLOCK_REFCOUNTING)
            cout << " - Указанный том поддерживает совместное использование логических кластеров между файлами на одном томе." << '\n';

        //Конец расшифровка lpFileSystemFlags

        cout << "Имя файловой системы:      " << lpFileSystemNameBuffer << '\n';
    }

    if (GetDiskFreeSpace(name, &sectorsPerCluster, &bytesPerSector,
        &numberOfFreeClusters, &totalNumberOfClusters)) {
        cout << '\n' << "- Число секторов в кластере: " << sectorsPerCluster << '\n';
        cout << "- Число байт в секторе: " << bytesPerSector << '\n';
        cout << "- Число свободных кластеров: " << numberOfFreeClusters << '\n';
        cout << "- Общее число кластеров: " << totalNumberOfClusters << '\n';
    }

    system("pause");
}

// Создание и удаление каталогов
void CreatingDirectories() {
    int catalogMenu;
    string disk_name;
    wstring w_string;
    LPCWSTR direct_name;

    do
    {
        cout << "+---+-------------------+" << '\n';
        cout << "| 1 | создание каталога |" << '\n';
        cout << "+---+-------------------+" << '\n';
        cout << "| 2 | удаление каталога |" << '\n';
        cout << "+---+-------------------+" << '\n';
        cout << "| 0 | выход             |" << '\n';
        cout << "+---+-------------------+" << '\n';

        cin >> catalogMenu;
        switch (catalogMenu)
        {
        case 1:
            cout << "Введите имя каталога (пример: c:\\folder): ";
            cin >> disk_name;

            //CreateDirectory

            w_string = wstring(disk_name.begin(), disk_name.end());
            direct_name = w_string.c_str();
            if (!CreateDirectory(direct_name, nullptr)) {
                cout << "Каталог не удалось создать! Ошибка." << '\n';
            }
            else {
                cout << "Каталог создан." << '\n';
            }
            break;

        case 2:

            cout << "Введите имя каталога (пример: c:\\folder): ";
            cin >> disk_name;

            //RemoveDirectory

            w_string = wstring(disk_name.begin(), disk_name.end());
            direct_name = w_string.c_str();

            if (!RemoveDirectory(direct_name)) {
                cout << "Каталог не удалось удалить! Ошибка." << '\n';
            }
            else {
                cout << "Каталог удален." << '\n';
            }

            system("pause");
            break;
        }

    } while (catalogMenu != 0);
    
}

// Создание в указаном каталоге
void CreationInTheSpecifiedDirectory() {
    string disk_name;
    wstring w_string;
    LPCWSTR file_name;

    cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
    cin >> disk_name;

    //CreateFile

    w_string = wstring(disk_name.begin(), disk_name.end());
    file_name = w_string.c_str();
    if (CreateFile(file_name, GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) == INVALID_HANDLE_VALUE) {
        cout << "Файл не удалось создать. Код ошибки: " << GetLastError();
    }
    else {
        cout << "Файл успешно создан." << '\n';
    }

    system("pause");
}

// Копирование и перемещение файлов между каталогами
void CopAndMovFiles() {
    int copnmovMenu;
    int moveFileEx_temp;
    string where_to;
    string which_one_to;
    wstring w_where_to;
    wstring w_which_one_to;

    LPCWSTR firstFile;
    LPCWSTR secondFile;

    do
    {
        cout << "+---+--------------------------------+" << '\n';
        cout << "| 1 | копировать файл                |\n";
        cout << "+---+--------------------------------+" << '\n';
        cout << "| 2 | переместить файл               |\n";
        cout << "+---+--------------------------------+" << '\n';
        cout << "| 3 | переместить файл (с проверкой) |\n";
        cout << "+---+--------------------------------+" << '\n';
        cout << "| 0 | выход                          |\n";
        cout << "+---+--------------------------------+" << '\n';

        cin >> copnmovMenu;
        system("cls");
        switch (copnmovMenu)
        {
        case 1:
            cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
            cin >> where_to;
            cout << "Введите адрес назначения (пример: c:\\folder\\text.pdf): ";
            cin >> which_one_to;

            // CopyFile

            w_where_to = wstring(where_to.begin(), where_to.end());
            firstFile = w_where_to.c_str();
            w_which_one_to = wstring(which_one_to.begin(), which_one_to.end());
            secondFile = w_which_one_to.c_str();

            if (CopyFile(firstFile, secondFile, false))
            {
                cout << "Файл успешно скопирован." << endl;
            }
            else {
                cout << "Ошибка! Не удалось скопировать файл. Код ошибки: " << GetLastError() << endl;
            }

            system("pause");
            break;

        case 2:
            cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
            cin >> where_to;
            cout << "Введите адрес назначения (пример: c:\\folder\\text.pdf): ";
            cin >> which_one_to;

            //MoveFile

            w_where_to = wstring(where_to.begin(), where_to.end());
            firstFile = w_where_to.c_str();
            w_which_one_to = wstring(which_one_to.begin(), which_one_to.end());
            secondFile = w_which_one_to.c_str();

            if (MoveFile(firstFile, secondFile)) {
                cout << "Файл успешно перемещен." << endl;
            }
            else {
                cout << "Ошибка! Не удалось переместить файл. Код ошибки: " << GetLastError() << endl;
            }

            system("pause");
            break;

        case 3:
            cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
            cin >> where_to;
            cout << "Введите адрес назначения (пример: c:\\folder\\text.pdf): ";
            cin >> which_one_to;

            //MoveFileEx

            w_where_to = wstring(where_to.begin(), where_to.end());
            firstFile = w_where_to.c_str();
            w_which_one_to = wstring(which_one_to.begin(), which_one_to.end());
            secondFile = w_which_one_to.c_str();

            moveFileEx_temp = 0;

            if (MoveFileEx(firstFile, secondFile, NULL)) {
                cout << "Файл или каталог успешно перемещен!" << endl;
            }
            else if (GetLastError() == 183) {
                cout << "Уже существует такой файл в данном каталоге. Заменить его?" << endl;
                cout << "+---+-----+" << endl;
                cout << "| 1 | Да  |" << endl;
                cout << "+---+-----+" << endl;
                cout << "| 0 | Нет |" << endl;
                cout << "+---+-----+" << endl;

                cin >> moveFileEx_temp;
                system("cls");

                if (moveFileEx_temp)
                {
                    if (MoveFileEx(firstFile, secondFile, MOVEFILE_REPLACE_EXISTING))
                    {
                        cout << "Файл или каталог успешно перемещен!" << endl;
                    }
                    else {
                        cout << "Ошибка! Не удалось переместить файл. Код ошибки: " << GetLastError() << endl;
                    }
                }
            }
            else {
                cout << "Ошибка! Не удалось переместить файл. Код ошибки: " << GetLastError() << endl;
            }

            system("pause");
            break;

        default:
            break;
        }
    } while (copnmovMenu != 0);
    
}

// Анализ и изменение атрибутов файлов
void AnalAndModFile() {
    int menu;

    PrintMenuAttributes();
    cin >> menu;

    system("cls");

    switch (menu) {
    case 1:
        FileAttributesGet();
        break;

    case 2:
        FileAttributesChange();
        break;

    case 3:
        FileInformationByHandle();
        break;

    case 4:
        FileTimeGet();
        break;

    case 5:
        FileTimeSet();
        break;
    }
}

// Получение атрибутов файла
void FileAttributesGet() {
    string disk_name;
    wstring w_string;

    LPCWSTR file_name;
    DWORD attribute;

    cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
    cin >> disk_name;

    //GetFileAttributes

    w_string = wstring(disk_name.begin(), disk_name.end());
    file_name = w_string.c_str();
    attribute = GetFileAttributes(file_name);

    if (attribute == 0) {
        cout << "Ошибка! Не удалось получить атрибуты файла." << endl;
    }
    else if (attribute == -1) {
        cout << "Ошибка! Файл не найден." << endl;
    }
    else {
        cout << "Атрибуты файла (" << attribute << "):" << endl;
        if (FILE_ATTRIBUTE_ARCHIVE & attribute) cout << "- Архивный файл" << endl;
        if (FILE_ATTRIBUTE_COMPRESSED & attribute) cout << "- Сжатый файл" << endl;
        if (FILE_ATTRIBUTE_DIRECTORY & attribute) cout << "- Каталог" << endl;
        if (FILE_ATTRIBUTE_HIDDEN & attribute) cout << "- Скрытый файл или каталог" << endl;
        if (FILE_ATTRIBUTE_NORMAL & attribute) cout << "- Файл не имеет атрибутов" << endl;
        if (FILE_ATTRIBUTE_READONLY & attribute) cout << "- Файл только для чтения" << endl;
    }

    system("pause");
}

// Изменение атрибутов файла
void FileAttributesChange() {
    string disk_name;
    wstring w_string;

    LPCWSTR file_name;

    DWORD setAttr;

    cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
    cin >> disk_name;

    //SetFileAttributes

    w_string = wstring(disk_name.begin(), disk_name.end());
    file_name = w_string.c_str();

    cout << "Изменить атрибут файла на:" << endl;
    cout << "+---+-------------------------+" << endl;
    cout << "| 1 | Архивный файл           |" << endl;
    cout << "+---+-------------------------+" << endl;
    cout << "| 2 | Скрытый файл            |" << endl;
    cout << "+---+-------------------------+" << endl;
    cout << "| 3 | Файл без атрибутов      |" << endl;
    cout << "+---+-------------------------+" << endl;
    cout << "| 4 | Файл только для чтения  |" << endl;
    cout << "+---+-------------------------+" << endl;
    cout << "| 5 | Системный файл          |" << endl;
    cout << "+---+-------------------------+" << endl;

    cin >> setAttr;

    switch (setAttr) {
    case 1:
        if (SetFileAttributes(file_name,
            FILE_ATTRIBUTE_ARCHIVE)) {
            cout << "Атрибут файла успешно изменен!" << endl;
        }
        else {
            cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
        }
        break;
    case 2:
        if (SetFileAttributes(file_name,
            FILE_ATTRIBUTE_HIDDEN)) {
            cout << "Атрибут файла успешно изменен!" << endl;
        }
        else {
            cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
        }
        break;
    case 3:
        if (SetFileAttributes(file_name,
            FILE_ATTRIBUTE_NORMAL)) {
            cout << "Атрибут файла успешно изменен!" << endl;
        }
        else {
            cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
        }
        break;
    case 4:
        if (SetFileAttributes(file_name,
            FILE_ATTRIBUTE_READONLY)) {
            cout << "Атрибут файла успешно изменен!" << endl;
        }
        else {
            cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
        }
        break;
    case 5:
        if (SetFileAttributes(file_name,
            FILE_ATTRIBUTE_SYSTEM)) {
            cout << "Атрибут файла успешно изменен!" << endl;
        }
        else {
            cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
        }
        break;
    }
    system("pause");
    system("cls");
}

// Получение информации о файле с помощью дескриптора
void FileInformationByHandle() {
    string disk_name;

    long handleInfo, FileAttributes;
    BY_HANDLE_FILE_INFORMATION infoFile;
    HANDLE handleFile;

    cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
    cin >> disk_name;

    handleFile = CreateFileA((LPCSTR)disk_name.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    handleInfo = GetFileInformationByHandle(handleFile, &infoFile);
    if (!handleInfo)
        cout << " Произошла ошибка. Код ошибки: " << GetLastError() << endl;
    else {
        FileAttributes = infoFile.dwFileAttributes;
        if (FileAttributes == -1)
            cout << " Файл " << disk_name << " не найден." << endl;
        else {

            cout << "Информация о файле по дескриптору:" << endl;

            if (FileAttributes & FILE_ATTRIBUTE_ARCHIVE)
                cout << " Файл " << disk_name << " - архивный." << endl;
            if (FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                cout << " Файл " << disk_name << " - директория." << endl;
            if (FileAttributes & FILE_ATTRIBUTE_READONLY)
                cout << " Файл " << disk_name << " - только для чтения." << endl;
            if (FileAttributes & FILE_ATTRIBUTE_SYSTEM)
                cout << " Файл " << disk_name << " - системный." << endl;
            if (FileAttributes & FILE_ATTRIBUTE_COMPRESSED)
                cout << " Файл " << disk_name << " - сжатый." << endl;
            if (FileAttributes & FILE_ATTRIBUTE_HIDDEN)
                cout << " Файл " << disk_name << " - скрытый." << endl;
            if (FileAttributes & FILE_ATTRIBUTE_NORMAL)
                cout << " Таких атрибутов файл " << disk_name << " не имеет.";
            if (FileAttributes == 0)
                cout << " Произошла ошибка. Код ошибки: " << GetLastError() << endl;
        }

        cout << " Старшая часть уникального идентификатора связи с файлом: " << infoFile.nFileIndexHigh << endl;
        cout << " Порядковый номер тома, который содержит файл: " << infoFile.dwVolumeSerialNumber << endl;
        cout << " Старшая часть размера файла: " << infoFile.nFileSizeHigh << endl;
        cout << " Младшая часть размера файла: " << infoFile.nFileSizeLow << endl;
        cout << " Число связей с этим файлом: " << infoFile.nNumberOfLinks << endl;
        cout << " Младшая часть уникального идентификатора связи с файлом: " << infoFile.nFileIndexLow << endl;
    }
    handleInfo = CloseHandle(handleFile);
    cout << endl;

    system("pause");
}

// Установить время файла
void FileTimeGet() {
    string disk_name;

    LPCSTR fileLPC;

    HANDLE fileT;

    FILETIME timeCreate, timeLastAccess, timeLastWrite;
    FILETIME fileTime;

    SYSTEMTIME time;
    SYSTEMTIME systemTime;

    cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
    cin >> disk_name;

    //GetFileTime

    fileLPC = disk_name.c_str();
    fileT = CreateFileA(fileLPC, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (GetFileTime(fileT, &timeCreate, &timeLastAccess, &timeLastWrite))
    {
        FileTimeToSystemTime(&timeCreate, &time);
        cout << "Дата и время создания файла:                " <<
            time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour + 3 << ":" <<
            time.wMinute << ":" << time.wSecond << endl;
        FileTimeToSystemTime(&timeLastAccess, &time);
        cout << "Дата и время последнего обращения к файлу:  " <<
            time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour + 3 << ":" <<
            time.wMinute << ":" << time.wSecond << endl;
        FileTimeToSystemTime(&timeLastWrite, &time);
        cout << "Дата и время последней модификации файла:   " <<
            time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour + 3 << ":" <<
            time.wMinute << ":" << time.wSecond << endl;
    }
    else {
        cout << "Ошибка! Не удалось получить информацию о файле. Код ошибки: " << GetLastError() << endl;
    }

    system("pause");
}

// Получить время файла
void FileTimeSet() {
    string disk_name;

    LPCSTR fileLPC;

    HANDLE fileT;

    FILETIME timeCreate, timeLastAccess, timeLastWrite;
    FILETIME fileTime;

    SYSTEMTIME time;
    SYSTEMTIME systemTime;

    cout << "Введите имя файла (пример: c:\\folder\\text.pdf): ";
    cin >> disk_name;

    //SetFileTime

    fileLPC = disk_name.c_str();
    fileT = CreateFileA(fileLPC, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    GetSystemTime(&systemTime);
    SystemTimeToFileTime(&systemTime, &fileTime);
    if (SetFileTime(fileT, &fileTime, &fileTime, &fileTime))
    {
        cout << "Атрибуты времени заменены успешно!" << endl;
    }
    else {
        cout << "Ошибка! Код ошибки: " << GetLastError() << endl;
    }

    system("pause");
}