#include <a_samp>

#if !defined _samp_included
	#error "Please include a_samp or a_npc before botsync"
#endif

#include <foreach>

#if defined SendChat
	#define BOTSYNC_IS_BOT     (true)
#endif

#if defined BOTSYNC_IS_BOT
	#define BOTSYNC_LOCK_STRING "0"
	#define BOTSYNC_LOCK_CHAR   '0'

	#define BOTSYNC_IN_STR      "t"
	#define BOTSYNC_OUT_STR     "f"

	#define BOTSYNC_MESSAGE_BUFFER (20)
#else
	#define BOTSYNC_LOCK_STRING "1"
	#define BOTSYNC_LOCK_CHAR   '1'

	#define BOTSYNC_IN_STR      "f"
	#define BOTSYNC_OUT_STR     "t"

	#define BOTSYNC_MESSAGE_BUFFER (128)
#endif

#define BOTSYNC_MESSAGE_LENGTH (124)

#define BOTSYNC_FOLDER         "BotSync."

#define BOTSYNC_FILE_LENGTH    (20)

#define BOTSYNC_FILE           (BOTSYNC_FOLDER "%03d.%s.l"), (bot), (read ? (BOTSYNC_IN_STR) : (BOTSYNC_OUT_STR))

#if !defined isnull
	#define isnull(%0) \
		(((%0)[0] == '\0') || (((%0)[0] == '\1') && ((%0)[1] == '\0')))
#endif

forward
	OnBotSyncData(bot, const name[], const msg[]);

#if defined BOTSYNC_SYNC_FS || defined BOTSYNC_IS_BOT
	Itter_Create(BotSync, BOTSYNC_MESSAGE_BUFFER);

	forward
		BotSync_Tick();

	static
	bool:
		BotSync_GetLock(bot, bool:read)
	{
		new
			name[BOTSYNC_FILE_LENGTH];
		format(name, sizeof (name), BOTSYNC_FILE);
		if (fexist(name))
		{
			return false;
		}
		new
			File:fhnd = fopen(name, io_write);
		if (fhnd)
		{
			fwrite(fhnd, BOTSYNC_LOCK_STRING);
			fclose(fhnd);
			fhnd = fopen(name, io_read);
			if (fhnd)
			{
				if (fgetchar(fhnd, 0, false) == BOTSYNC_LOCK_CHAR)
				{
					fclose(fhnd);
					return true;
				}
				fclose(fhnd);
			}
			else
			{
				printf("BotSync error: Lock fail");
			}
		}
		return false;
	}

	static
		BotSync_ReleaseLock(bot, bool:read)
	{
		new
			name[BOTSYNC_FILE_LENGTH];
		format(name, sizeof (name), BOTSYNC_FILE);
		fremove(name);
	}

	static
	BSF:
		BotSync_Open(bot)
	{
		new
			name[BOTSYNC_FILE_LENGTH];
		format(name, sizeof (name), BOTSYNC_FOLDER "%03d." BOTSYNC_OUT_STR ".d", bot);
		return BSF:fopen(name, io_append);
	}

	#define BotSync_Write(%0,%1) \
		fwrite(File:%0, %1)

	#define BotSync_Close(%0) \
		fclose(File:%0)
#endif

#if defined BOTSYNC_IS_BOT
	static
		BS_g_MessageBuffer[BOTSYNC_MESSAGE_BUFFER][BOTSYNC_MESSAGE_LENGTH],
		BS_g_me;

	public
		BotSync_Tick()
	{
		if (Itter_Count(BotSync))
		{
			if (BotSync_GetLock(BS_g_me, false))
			{
				new
					BSF:fhnd = BotSync_Open(BS_g_me);
				if (fhnd)
				{
					new
						msg = YSI_gBotSyncS,
						nxt;
					while (msg != -1)
					{
						BotSync_Write(fhnd, BS_g_MessageBuffer[msg]);
						nxt = YSI_gBotSyncA[msg];
						YSI_gBotSyncA[msg] = -1;
						msg = nxt;
					}
					YSI_gBotSyncC = 0;
					YSI_gBotSyncS = -1;
					BotSync_Close(fhnd);
				}
				BotSync_ReleaseLock(BS_g_me, false);
			}
		}
		#if defined BOT_SYNC_CALLBACK
			new
				name[BOTSYNC_FILE_LENGTH];
			format(name, sizeof (name), BOTSYNC_FOLDER "%03d." BOTSYNC_IN_STR ".d", BS_g_me);
			if (fexist(name))
			{
				if (BotSync_GetLock(BS_g_me, true))
				{
					new
						File:fhnd = fopen(name, io_read);
					if (fhnd)
					{
						new
							str[BOTSYNC_MESSAGE_LENGTH];
						while (fread(fhnd, str))
						{
							new
								pos0 = -1;
							while (str[++pos0] > '\1') {}
							if (str[pos0] == '\1')
							{
								new
									pos1 = pos0;
								while (str[++pos1] >= ' ') {}
								str[pos0] = '\0';
								str[pos1] = '\0';
								BOT_SYNC_CALLBACK(-1, str, str[pos0 + 1]);
							}
						}
						fclose(fhnd);
						fremove(name);
					}
					BotSync_ReleaseLock(BS_g_me, true);
				}
			}
		#endif
	}

	public
		OnNPCConnect(myplayerid)
	{
		SetTimer("BotSync_Tick", 10, true);
		BS_g_me = myplayerid;
		BotSync_OnNPCConnect(myplayerid);
	}

	#define OnNPCConnect BotSync_OnNPCConnect

	forward
		BotSync_OnNPCConnect(myplayerid);

	public
		OnClientMessage(color, text[])
	{
		if (color)
		{
			return BotSync_OnClientMessage(color, text);
		}
		new
			pos0 = -1;
		while (text[++pos0] > '\1') {}
		if (text[pos0] == '\1')
		{
			text[pos0] = '\0';
			BOT_SYNC_CALLBACK(-1, text, text[pos0 + 1]);
		}
		return 0;
	}

	#define OnClientMessage BotSync_OnClientMessage

	forward
		BotSync_OnClientMessage(color, text[]);

	stock
		BotSync_Send(bot, type[], message[])
	{
		new
			slot = Itter_Free(BotSync);
		if (slot != -1)
		{
			if (strlen(type) + strlen(message) < BOTSYNC_MESSAGE_LENGTH - 3)
			{
				format(BS_g_MessageBuffer[slot], BOTSYNC_MESSAGE_LENGTH, "%s\1%s\n", type, message);
				Itter_Add(BotSync, slot);
				return 1;
			}
		}
		return 0;
		#pragma unused bot
	}
#else
	#if defined BOTSYNC_SYNC_FS
		enum E_BOTSYNC_BUFFER
		{
			E_BOTSYNC_BOT,
			E_BOTSYNC_MESSAGE[BOTSYNC_MESSAGE_LENGTH]
		}

		static
			BS_g_MessageBuffer[BOTSYNC_MESSAGE_BUFFER][E_BOTSYNC_BUFFER];

		forward
			BotSync_Buffer(bot, type[], message[]);

		public
			BotSync_Tick()
		{
			new
				dun = -1,
				msg,
				last;
			do
			{
				last = -1;
				foreachex (BotSync, msg)
				{
					if (msg > dun)
					{
						new
							bot = BS_g_MessageBuffer[msg][E_BOTSYNC_BOT];
						if (BotSync_GetLock(bot, false))
						{
							new
								BSF:fhnd = BotSync_Open(bot);
							if (fhnd)
							{
								BotSync_Write(fhnd, BS_g_MessageBuffer[msg][E_BOTSYNC_MESSAGE]);
								new
									cur = YSI_gBotSyncA[msg],
									lst = msg;
								while (cur != -1)
								{
									if (BS_g_MessageBuffer[cur][E_BOTSYNC_BOT] == bot)
									{
										BotSync_Write(fhnd, BS_g_MessageBuffer[cur][E_BOTSYNC_MESSAGE]);
										YSI_gBotSyncA[lst] = YSI_gBotSyncA[cur];
										YSI_gBotSyncA[cur] = -1;
										cur = YSI_gBotSyncA[lst];
										--YSI_gBotSyncC;
									}
									else
									{
										lst = cur;
										cur = YSI_gBotSyncA[cur];
									}
								}
								BotSync_Close(fhnd);
								BotSync_ReleaseLock(bot, false);
								dun = msg;
								if (last == -1)
								{
									YSI_gBotSyncS = YSI_gBotSyncA[msg];
								}
								else
								{
									YSI_gBotSyncA[last] = YSI_gBotSyncA[msg];
								}
								YSI_gBotSyncA[msg] = -1;
								--YSI_gBotSyncC;
								break;
							}
							BotSync_ReleaseLock(bot, false);
						}
					}
					last = msg;
				}
			}
			while (msg != -1);
			foreach (Bot, bot)
			{
				new
					name[BOTSYNC_FILE_LENGTH];
				format(name, sizeof (name), BOTSYNC_FOLDER "%03d." BOTSYNC_IN_STR ".d", bot);
				if (fexist(name))
				{
					if (BotSync_GetLock(bot, true))
					{
						new
							File:fhnd = fopen(name, io_read);
						if (fhnd)
						{
							new
								str[BOTSYNC_MESSAGE_LENGTH];
							while (fread(fhnd, str))
							{
								new
									pos0 = -1;
								while (str[++pos0] > '\1') {}
								if (str[pos0] == '\1')
								{
									new
										pos1 = pos0;
									while (str[++pos1] >= ' ') {}
									str[pos0] = '\0';
									str[pos1] = '\0';
									CallRemoteFunction("OnBotSyncData", "iss", bot, str, str[pos0 + 1]);
								}
							}
							fclose(fhnd);
							fremove(name);
						}
						BotSync_ReleaseLock(bot, true);
					}
				}
			}
		}

		public
			BotSync_Buffer(bot, type[], message[])
		{
			// Buffer the message and send it later.
			if (isnull(type) || isnull(message))
			{
				return 0;
			}
			if (IsPlayerNPC(bot))
			{
				new
					slot = Itter_Free(BotSync);
				if (slot != -1)
				{
					if (strlen(type) + strlen(message) < BOTSYNC_MESSAGE_LENGTH - 3)
					{
						format(BS_g_MessageBuffer[slot][E_BOTSYNC_MESSAGE], BOTSYNC_MESSAGE_LENGTH, "%s\1%s\n", type, message);
						BS_g_MessageBuffer[slot][E_BOTSYNC_BOT] = bot;
						Itter_Add(BotSync, slot);
						return 1;
					}
				}
			}
			return 0;
		}
	#else
		stock
			BotSync_SendFast(bot, type[], message[])
		{
			if (IsPlayerNPC(bot))
			{
				if (strlen(type) + strlen(message) < BOTSYNC_MESSAGE_LENGTH - 3)
				{
					new
						str[BOTSYNC_MESSAGE_LENGTH];
					format(str, sizeof (str), "%s\1%s", type, message);
					SendClientMessage(bot, 0, str);
					return 1;
				}
			}
			return 0;
		}

		stock
			BotSync_Send(bot, type[], message[])
		{
			CallRemoteFunction("BotSync_Buffer", "iss", bot, type, message);
		}
	#endif
#endif
