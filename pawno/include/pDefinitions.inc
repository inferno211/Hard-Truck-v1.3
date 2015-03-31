#define HOOD 1 //maska
#define TRUNK 2 //baga¿nik
#define LEFT_DOOR 3 //lewe drzwi
#define RIGHT_DOOR 4 //prawe drzwi

#define LEFT_F_TIRE 1 //Lewa przednia opona
#define LEFT_B_TIRE 2 //Lewa tylnia opona
#define RIGHT_F_TIRE 3 //Prawa przednia opona
#define RIGHT_B_TIRE 4 //Prawa tylnia opona

#define LEFT_LIGHT 1 //Lewa lampa
#define RIGHT_LIGHT 2 //Prawa lampa

#define FRONT_PANEL 1 //Przedni zderzak
#define BACK_PANEL 2 //Tylni zderzak

//STATUSY ELEMENTÓW
#define FULL 0 //Nieuszkodzony   (we wszystkich elementach)
#define OPENED 1 //otwarty     	 (tylko w masce, baga¿niku oraz drzwiach lewych i prawych)
#define DAMAGED 2 //uszkodzony   (we wszystkich elementach)
#define OPENED_DAMAGED 3 //otwarty-uszkodzony (tylko w masce, baga¿niku oraz drzwiach lewych i prawych)
#define REMOVED 4 //usuniêty 	 (we wszystkich elementach oprócz lamp œwietlnych i opon)
#define SHAKED 5 //zachwiany  	 (tylko w zderzakach)   






//NIE U¯YWAC TEGO
//NIE U¯YWAC TEGO
//NIE U¯YWAC TEGO
//NIE U¯YWAC TEGO

//Statusy elementow (binarnie - cstring)
#define IN_FULL "00000000" // 0
#define IN_OPENED "00000001" //1
#define IN_DAMAGED "00000010" //2
#define IN_OPENED_DAMAGED "00000011" //3
#define IN_REMOVED "00000100" //4
#define IN_FRONT_PANEL_FULL "00000000000000000000000"
#define IN_BACK_PANEL_FULL "000"
#define IN_BACK_PANEL_DAMAGED "100"
#define IN_BACK_PANEL_REMOVED "110"

//Funkcje pomocnicze
stock BinToDec(binary[])
{
	new suma = 0;
	new n = 0;
	new strtemp[50];
	strcat(strtemp,binary);
	for(new i = strlen(binary) - 1; i >= 0; i--)
	{
	    GetChar(i,binary);
		suma += strval(binary) * Power(2,n);
		strdel(binary,0,strlen(binary));
		strcat(binary,strtemp,strlen(strtemp));
		n++;
	}
	return suma;
}

stock Power(value, n)
{
	new suma;
	if(n == 0)
		suma = 1;

	else
 	suma = value;
	for(new i = 0; i < n - 1; i++)
	    suma *= value;

	return suma;
}

stock GetChar(index, string[])
{
	new temp = strlen(string);
	strdel(string,index + 1,temp);
	strdel(string,0,index);
}
