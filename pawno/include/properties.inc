#include <a_samp>
#include <dini>

forward org_OnGameModeInit();

enum frakcja
{
	FrakcjaSzef[15],
	FrakcjaNazwa[20],
}

new Frakcja[250][frakcja];

public org_OnGameModeInit()
{
	if(!dini_Exists("Organizacje/Konfiguracja.ini"))
	{
		dini_Create("Organizacje/Konfiguracja.ini");

		dini_IntSet("Organizacje/Konfiguracja.ini", "Ostatni_Numer", 0);
		
		printf("Pomyslnie stworzono plik konfiguracjny.\nRestart serwera.");
		SendRconCommand("gmx");
	}
}

stock StworzFrakcje(const nazwa[])
{
	new string[20];

	new string2[4];

	format(string2, sizeof(string2), "%d",dini_Int("Organizacje/Konfiguracja.ini", "Ostatni_Numer")+1);
	format(string, sizeof(string), "Organizacje/%d.ini", string2);

	Frakcja[strval(string2)][FrakcjaNazwa] = strlen(nazwa);

	printf("%s %d %s", string, string2, Frakcja[strval(string2)][FrakcjaNazwa]);

	if(!strlen(nazwa))
	{
	    print("[==========================================================]");
	    print("       Blad Organizacji:   Organizacja musi miec nazwe!     ");
	    print("            Ta organizacja nie zostala stworzona!           ");
	    print("[==========================================================]");

	    return 1;
	}



	dini_Create(string);

	dini_Set(string, "Nazwa", Frakcja[strval(string2)][FrakcjaNazwa]);
	dini_Set(string, "Szef", "");

	return 1;
}