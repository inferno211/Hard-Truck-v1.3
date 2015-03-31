/*
Nazwa: rFile
Pe³na nazwa: Simple & Fast File System
Autor: RPS
Wersja 1.0 R2
Ostatnia aktualizacja: 27.09.2010

Funkcje:

native Simple & Fast File System by RPS
native
native Read(playerid);
native Save(playerid);
native Delete(playerid);
native DeleteOption(playerid, option[]);
native
native ReadFile(const filename[], const ID);
native SaveFile(const filename[], const ID);
native DeleteFile(const filename[]);
native DeleteFileOption(const ID, option[]);
native
native rSetStr(playerid, option[], definition[]);
native rSetInt(playerid, option[], definition);
native rSetFloat(playerid, option[], Float:definition);
native rGetStr(playerid, option[]);
native rGetInt(playerid, option[]);
native rGetFloat(playerid, option[]);
native IsSet(playerid, option[]);
native
*/

#if defined _rFile_included
    #endinput
#endif
#define _rFile_included
#pragma library rFile

#define rKey "="
#define rINI ".ini"
#define RFILE_SIZE 128
#define MAX_PLAYERSS 50 // liczba slotów na serwerze
#define MAX_FILES (MAX_PLAYERSS + 10) // 10 - maksymalna liczba dodatkowych plików

#pragma dynamic 10000
new FileVar[MAX_FILES][10000];

stock PlayerF(playerid)
{
    new name[28];
    GetPlayerName(playerid, name, MAX_PLAYER_NAME);
    strins(name, rINI, strlen(name));
    return name;
}

stock IsSet(playerid, option[])
{
    new str[RFILE_SIZE];
    format(str, sizeof str, "%s%c", option, rKey);
    new pos = strfind(FileVar[playerid], str);

    if(pos == -1)
        return 0;
    else
        return 1;

}

stock DeleteFileOption(const ID, option[])
    DeleteOption(ID, option);

stock DeleteOption(playerid, option[])
{
    new str[RFILE_SIZE],
        pos;

    format(str, sizeof str, "%s%c", option, rKey);
    pos = strfind(FileVar[playerid], str);

    if(pos != -1)
    {
        strdel(FileVar[playerid], pos, strfind(FileVar[playerid], "\n", false, pos)+1);
        return 1;
    }
    else
        return 0;
}

stock Delete(playerid)
    fremove(PlayerF(playerid));

stock DeleteFile(const filename[])
    fremove(filename);

stock Save(playerid)
{
    if(strlen(FileVar[playerid]) == 0)
        return 0;

    new File:Fid = fopen(PlayerF(playerid), io_write);
    fwrite(Fid, FileVar[playerid]);
    fclose(Fid);
    FileVar[playerid][0] = EOS;
    return 1;
}

stock SaveFile(const filename[], const ID)
{
    if(strlen(FileVar[ID]) == 0)
        return 0;

    new File:Fid = fopen(filename, io_write);
    fwrite(Fid, FileVar[ID]);
    fclose(Fid);
    FileVar[ID][0] = EOS;
    return 1;
}

stock Read(playerid)
{
    new str[RFILE_SIZE],
        File:Fid = fopen(PlayerF(playerid), io_readwrite);

    while(fread(Fid, str))
        strins(FileVar[playerid], str, strlen(FileVar[playerid]));

    fclose(Fid);
    fremove(PlayerF(playerid));
}

stock ReadFile(const filename[], const ID)
{
    new str[RFILE_SIZE],
        File:Fid = fopen(filename, io_readwrite);

    while(fread(Fid, str))
        strins(FileVar[ID], str, strlen(FileVar[ID]));

    fremove(filename);
    return 1;
}

stock rSetStr(playerid, option[], definition[])
{
    new str[RFILE_SIZE];
    format(str, sizeof str, "%s%c", option, rKey);
    new pos = strfind(FileVar[playerid], str, false, 0);

    if(pos == -1)
    {
        format(str, sizeof str, "%s%c%s\r\n", option, rKey, definition);
        strins(FileVar[playerid], str, strlen(FileVar[playerid]));
    }
    else
    {
        strdel(FileVar[playerid], pos-1, strfind(FileVar[playerid], "\n", false, pos));
        format(str, sizeof str, "%s%c%s\r\n", option, rKey, definition);
        strins(FileVar[playerid], str, strlen(FileVar[playerid]));
    }
}

stock rSetInt(playerid, option[], definition)
{
    new str[RFILE_SIZE];
    valstr(str, definition);
    rSetStr(playerid, option, str);
}

stock rSetFloat(playerid, option[], Float:definition)
{
    new str[RFILE_SIZE];
    format(str, sizeof str, "%f", definition);
    rSetStr(playerid, option, str);
}

stock rGetStr(playerid, option[])
{
    new str[RFILE_SIZE],
        strex[RFILE_SIZE],
        pos;

    format(strex, sizeof strex, "%s%c", option, rKey);
    pos = strfind(FileVar[playerid], strex);

    if(pos != -1)
    {
        strmid(str, FileVar[playerid], pos+strlen(strex), strfind(FileVar[playerid], "\n", false, pos+1)-1);
        return str;
    }
    else
        return str;
}

stock rGetInt(playerid, option[])
    return strval(rGetStr(playerid, option));

stock Float:rGetFloat(playerid, option[])
    return floatstr(rGetStr(playerid, option));
