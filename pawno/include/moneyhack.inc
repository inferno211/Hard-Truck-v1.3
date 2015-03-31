new current_amount[MAX_PLAYERS];
new given_amount[MAX_PLAYERS];

forward MoneyCheck(playerid);

stock GivePlayerMoney2(playerid,amount)
{
    given_amount[playerid] = amount;
    GivePlayerMoney(playerid,given_amount[playerid]);
    current_amount[playerid] = GetPlayerMoney(playerid); 
    return 1;
}

public MoneyCheck(playerid)
{
    if(current_amount[playerid] != GetPlayerMoney(playerid)){
        ResetPlayerMoney(playerid);
        GivePlayerMoney(playerid,current_amount[playerid]);
    }
    return 1;
}