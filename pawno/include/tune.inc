stock TunePlayerVehicle(PlayerId)
{
	new carid = GetPlayerVehicleID(PlayerId);
	RepairVehicle(carid);
	ChangeVehicleColor(carid,174,174);

	new modelid;
	modelid = GetVehicleModel(carid);
	switch(modelid)
	{
		case 405,477,411,429,402,589,494,541,
			451,506,434,603,415,409,602,437,
		 	439,480,550,579,416,587,403,504,
		 	568,514,475,596,599:
		{
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1081);
		}
		case 432,531,601:
		{
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1081);
		}

		case 557:
		{
			AddVehicleComponent(carid,1010);
		}

		case 420:
		{
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1081);
			AddVehicleComponent(carid,1139);
		}

		case 534:
		{
			ChangeVehiclePaintjob(carid,2);
			AddVehicleComponent(carid,1180);
			AddVehicleComponent(carid,1185);
			AddVehicleComponent(carid,1100);
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1127);
			AddVehicleComponent(carid,1101);
			AddVehicleComponent(carid,1122);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1080);
		}
		case 535:
		{
			ChangeVehiclePaintjob(carid,2);
			AddVehicleComponent(carid,1109);
			AddVehicleComponent(carid,1115);
			AddVehicleComponent(carid,1117);
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1114);
			AddVehicleComponent(carid,1081);
			AddVehicleComponent(carid,1119);
			AddVehicleComponent(carid,1121);
		}
		case 536:
		{
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1183);
			AddVehicleComponent(carid,1181);
			AddVehicleComponent(carid,1107);
			AddVehicleComponent(carid,1104);
			AddVehicleComponent(carid,1108);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1082);
			ChangeVehiclePaintjob(carid,random(2)+1);
		}
		case 558:
		{
			AddVehicleComponent(carid,1092);
			AddVehicleComponent(carid,1166);
			AddVehicleComponent(carid,1165);
			AddVehicleComponent(carid,1090);
			AddVehicleComponent(carid,1094);
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1163);
			AddVehicleComponent(carid,1091);
			AddVehicleComponent(carid,1080);
			ChangeVehiclePaintjob(carid,random(2)+1);
		}
		case 559:
		{
			AddVehicleComponent(carid,1070);
			AddVehicleComponent(carid,1066);
			AddVehicleComponent(carid,1072);
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1147);
			AddVehicleComponent(carid,1068);
			AddVehicleComponent(carid,1080);
			AddVehicleComponent(carid,1173);
			AddVehicleComponent(carid,1161);
			ChangeVehiclePaintjob(carid,random(2)+1);
		}
		case 560:
		{
			AddVehicleComponent(carid,1028);
			AddVehicleComponent(carid,1140);
			AddVehicleComponent(carid,1170);
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1139);
			AddVehicleComponent(carid,1033);
			AddVehicleComponent(carid,1080);
			AddVehicleComponent(carid,1031);
			AddVehicleComponent(carid,1030);
			ChangeVehiclePaintjob(carid,random(2)+1);
		}
		case 561:
		{
			AddVehicleComponent(carid,1056);
			AddVehicleComponent(carid,1156);
			AddVehicleComponent(carid,1157);
			AddVehicleComponent(carid,1062);
			AddVehicleComponent(carid,1059);
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1146);
			AddVehicleComponent(carid,1080);
			AddVehicleComponent(carid,1061);
			ChangeVehiclePaintjob(carid,random(2)+1);
		}
		case 562:
		{
			ChangeVehiclePaintjob(carid,random(2)+1);
			AddVehicleComponent(carid,1037);
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1035);
			AddVehicleComponent(carid,1039);
			AddVehicleComponent(carid,1041);
			AddVehicleComponent(carid,1086);
			AddVehicleComponent(carid,1080);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1147);
			AddVehicleComponent(carid,1148);
			AddVehicleComponent(carid,1172);
		}
		case 565:
		{
			ChangeVehiclePaintjob(carid,random(2)+1);
			AddVehicleComponent(carid,1046);
			AddVehicleComponent(carid,1151);
			AddVehicleComponent(carid,1152);
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1087);
			AddVehicleComponent(carid,1139);
			AddVehicleComponent(carid,1080);
			AddVehicleComponent(carid,1081);
			AddVehicleComponent(carid,1053);
			AddVehicleComponent(carid,1047);
			AddVehicleComponent(carid,1051);
		}
		case 567:
		{
			AddVehicleComponent(carid,1188);
			AddVehicleComponent(carid,1186);
			AddVehicleComponent(carid,1102);
			AddVehicleComponent(carid,1133);
			AddVehicleComponent(carid,1018);
			AddVehicleComponent(carid,1010);
			AddVehicleComponent(carid,1080);
			AddVehicleComponent(carid,1087);
			ChangeVehiclePaintjob(carid,random(2)+1);
			AddVehicleComponent(carid,1081);

		}
		default:
		{
			return 0;
		}
	}
	return 1;
}