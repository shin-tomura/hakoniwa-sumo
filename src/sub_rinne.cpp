
	while( !ProcessMessage() )
	{
		for (i=0;i<37;i++){
			if (edittarget!=i && i!=3 && i!=23){
				if (i>=0 && i<=15){
					if (get_mouseclick(233,104+i*16,233+20,104+i*16+12)){
						edittarget=i;
						edittargethenkan(x);
					}
				}else if (i>=16 && i<=28){
					if (get_mouseclick(333,104+(i-16)*16,333+20,104+(i-16)*16+12)){
						edittarget=i;
						edittargethenkan(x);
					}
				}else if (i>=29 && i<=36){
					if (get_mouseclick(433,104+(i-29)*16,433+20,104+(i-29)*16+12)){
						edittarget=i;
						edittargethenkan(x);
					}
				}
			}
		}
		for (i=100;i<137;i++){
			if (edittarget!=i && i!=102 && i!=124 && i!=127 && i!=128){
				if (i>=100 && i<=115){
					if (get_mouseclick(255,104+(i-100)*16,255+20,104+(i-100)*16+12)){
						edittarget=i;
						edittargethenkan(x);
					}
				}else if (i>=116 && i<=128){
					if (get_mouseclick(355,104+(i-116)*16,355+20,104+(i-116)*16+12)){
						edittarget=i;
						edittargethenkan(x);
					}
				}else if (i>=129 && i<=136){
					if (get_mouseclick(455,104+(i-129)*16,455+20,104+(i-129)*16+12)){
						edittarget=i;
						edittargethenkan(x);
					}
				}
			}
		}
		if( ProcessMessage() == -1 ){mode=1;return -1;}
		//ƒXƒŠ[ƒv
		Sleep(1);
	}






			switch(edittarget){	
			case 0:
				temp_value=rikisidata[x].binshousei;
				rikisidata[x].sinchou=kaeri;
				rikisidata[x].binshousei=60-(int)((rikisidata[x].sinchou-159)/2)-(int)((rikisidata[x].taijuu-69)/5)+rikisidata[x].binshousei_natural;
				if ( ((int)(((169-rikisidata[x].sinchou)*(-3))/2)+140) < rikisidata[x].taijuu ){
					rikisidata[x].binshousei-=(rikisidata[x].taijuu-((int)(((169-rikisidata[x].sinchou)*(-3))/2)+140))*2;
				}
				if (rikisidata[x].binshousei<10) rikisidata[x].binshousei=10;
				if (rikisidata[x].binshousei>99) rikisidata[x].binshousei=99;
				rikisidata[x].stamina+=rikisidata[x].binshousei-temp_value;
				break;
			case 1:
				temp_value=rikisidata[x].binshousei;
				rikisidata[x].taijuu=kaeri;
				rikisidata[x].binshousei=60-(int)((rikisidata[x].sinchou-159)/2)-(int)((rikisidata[x].taijuu-69)/5)+rikisidata[x].binshousei_natural;
				if ( ((int)(((169-rikisidata[x].sinchou)*(-3))/2)+140) < rikisidata[x].taijuu ){
					rikisidata[x].binshousei-=(rikisidata[x].taijuu-((int)(((169-rikisidata[x].sinchou)*(-3))/2)+140))*2;
				}
				if (rikisidata[x].binshousei<10) rikisidata[x].binshousei=10;
				if (rikisidata[x].binshousei>99) rikisidata[x].binshousei=99;
				rikisidata[x].stamina+=rikisidata[x].binshousei-temp_value;
				break;
			case 2:
				rikisidata[x].sekkyokusei=kaeri;
				break;
			case 4:
				rikisidata[x].tossinryoku=kaeri;
				break;
			case 5:
				rikisidata[x].kerutikara=kaeri;
				break;
			case 6:
				rikisidata[x].migiwanryoku=kaeri;
				break;
			case 7:
				rikisidata[x].hidariwanryoku=kaeri;
				break;
			case 8:
				rikisidata[x].balance=kaeri;
				break;
			case 9:
				rikisidata[x].tatiaigijutu=kaeri;
				break;
			case 10:
				rikisidata[x].tuki=kaeri;
				break;
			case 11:
				rikisidata[x].migiwakikatasa=kaeri;
				break;
			case 12:
				rikisidata[x].hidariwakikatasa=kaeri;
				break;
			case 13:
				rikisidata[x].ategai=kaeri;
				break;
			case 14:
				rikisidata[x].migikaesi=kaeri;
				break;
			case 15:
				rikisidata[x].hidarikaesi=kaeri;
				break;
			case 16:
				rikisidata[x].migisibori=kaeri;
				break;
			case 17:
				rikisidata[x].hidarisibori=kaeri;
				break;
			case 18:
				rikisidata[x].migikakaekomi=kaeri;
				break;
			case 19:
				rikisidata[x].hidarikakaekomi=kaeri;
				break;
			case 20:
				rikisidata[x].hikituke=kaeri;
				break;
			case 21:
				rikisidata[x].migiakuryoku=kaeri;
				break;
			case 22:
				rikisidata[x].hidariakuryoku=kaeri;
				break;
			case 24:
				rikisidata[x].konjou=kaeri;
				break;
			case 25:
				rikisidata[x].nebari=kaeri;
				break;
			case 26:
				rikisidata[x].asihakobi=kaeri;
				break;
			case 27:
				rikisidata[x].juunansei=kaeri;
				break;
			case 28:
				rikisidata[x].zunou=100-kaeri;
				break;
			case 29:
				rikisidata[x].migiuwatenage=kaeri;
				break;
			case 30:
				rikisidata[x].hidariuwatenage=kaeri;
				break;
			case 31:
				rikisidata[x].migisitatenage=kaeri;
				break;
			case 32:
				rikisidata[x].hidarisitatenage=kaeri;
				break;
			case 33:
				rikisidata[x].migikotenage=kaeri;
				break;
			case 34:
				rikisidata[x].hidarikotenage=kaeri;
				break;
			case 35:
				rikisidata[x].migisukuinage=kaeri;
				break;
			case 36:
				rikisidata[x].hidarisukuinage=kaeri;
				break;
			case 100:
				rikisidata[x].sinchou_max=kaeri;
				break;
			case 101:
				rikisidata[x].taijuu_max=kaeri;
				break;
			case 103:
				temp_value=rikisidata[x].binshousei;
				rikisidata[x].binshousei_natural=kaeri;
				rikisidata[x].binshousei=60-(int)((rikisidata[x].sinchou-159)/2)-(int)((rikisidata[x].taijuu-69)/5)+rikisidata[x].binshousei_natural;
				if ( ((int)(((169-rikisidata[x].sinchou)*(-3))/2)+140) < rikisidata[x].taijuu ){
					rikisidata[x].binshousei-=(rikisidata[x].taijuu-((int)(((169-rikisidata[x].sinchou)*(-3))/2)+140))*2;
				}
				if (rikisidata[x].binshousei<10) rikisidata[x].binshousei=10;
				if (rikisidata[x].binshousei>99) rikisidata[x].binshousei=99;
				rikisidata[x].stamina+=rikisidata[x].binshousei-temp_value;
				break;
			case 104:
				rikisidata[x].tossinryoku_max=kaeri;
				break;
			case 105:
				rikisidata[x].kerutikara_max=kaeri;
				break;
			case 106:
				rikisidata[x].migiwanryoku_max=kaeri;
				break;
			case 107:
				rikisidata[x].hidariwanryoku_max=kaeri;
				break;
			case 108:
				rikisidata[x].balance_max=kaeri;
				break;
			case 109:
				rikisidata[x].tatiaigijutu_max=kaeri;
				break;
			case 110:
				rikisidata[x].tuki_max=kaeri;
				break;
			case 111:
				rikisidata[x].migiwakikatasa_max=kaeri;
				break;
			case 112:
				rikisidata[x].hidariwakikatasa_max=kaeri;
				break;
			case 113:
				rikisidata[x].ategai_max=kaeri;
				break;
			case 114:
				rikisidata[x].migikaesi_max=kaeri;
				break;
			case 115:
				rikisidata[x].hidarikaesi_max=kaeri;
				break;
			case 116:
				rikisidata[x].migisibori_max=kaeri;
				break;
			case 117:
				rikisidata[x].hidarisibori_max=kaeri;
				break;
			case 118:
				rikisidata[x].migikakaekomi_max=kaeri;
				break;
			case 119:
				rikisidata[x].hidarikakaekomi_max=kaeri;
				break;
			case 120:
				rikisidata[x].hikituke_max=kaeri;
				break;
			case 121:
				rikisidata[x].migiakuryoku_max=kaeri;
				break;
			case 122:
				rikisidata[x].hidariakuryoku_max=kaeri;
				break;
			case 123:
				temp_value=rikisidata[x].stamina_natural;
				rikisidata[x].stamina_natural=kaeri;
				rikisidata[x].stamina+=rikisidata[x].stamina_natural-temp_value;
				break;
			case 125:
				rikisidata[x].nebari_max=kaeri;
				break;
			case 126:
				rikisidata[x].asihakobi_max=kaeri;
				break;
			case 129:
				rikisidata[x].migiuwatenage_max=kaeri;
				break;
			case 130:
				rikisidata[x].hidariuwatenage_max=kaeri;
				break;
			case 131:
				rikisidata[x].migisitatenage_max=kaeri;
				break;
			case 132:
				rikisidata[x].hidarisitatenage_max=kaeri;
				break;
			case 133:
				rikisidata[x].migikotenage_max=kaeri;
				break;
			case 134:
				rikisidata[x].hidarikotenage_max=kaeri;
				break;
			case 135:
				rikisidata[x].migisukuinage_max=kaeri;
				break;
			case 136:
				rikisidata[x].hidarisukuinage_max=kaeri;
				break;
			}
