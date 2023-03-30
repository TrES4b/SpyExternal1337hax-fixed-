#pragma once
#include "asm.cpp"

#ifdef BSP_PARSER
#include "bsp_parser.h"
using namespace rn;
bsp_parser* bspParser = new bsp_parser;
bool mapparsed = false;
#endif

TCHAR MYname[32];
TCHAR MYclan[32];
void Prepare()
{

}

void Finalize()
{
	
}

void NameStealer()
{
	int maxplayers = 64; $$$;
	TCHAR name[32], clan[32]; $$$;
	int rando, old = 65; $$$;

	while (true)
	{
		Sleep(1); $$$;
	}
}

void Bunnyhop()
{
#define FORCE_JUMP_BITMASK (1<<0)
	std::bitset<8> dwForceJumpBitMask{ 0b0000'0001 }; $$$;
	int currJumpState{ 0 }; $$$;

	float VisY, VisYnew; $$$;
	float VisYd; $$$;
	BYTE onGround = 1; $$$;

	while (true)
	{
		if (cheat(AY_OBFUSCATE("Bunnyhop & Autostrafe")) == 1 && tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_SPACE) < 0 && rvm<DWORD>(clientstate + dwClientState_State) == 6)
		{
			VisY = rvm<float>(clientstate + dwClientState_ViewAngles + 4); $$$;
			VisYnew = VisY; $$$;

			while (cheat(AY_OBFUSCATE("Bunnyhop & Autostrafe")) == 1 && tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_SPACE) < 0)
			{
				VisYnew = rvm<float>(clientstate + dwClientState_ViewAngles + 4); $$$;
				if (VisY != VisYnew) //Y changed?
				{
					VisYd = 1 * (VisY - VisYnew); $$$;
					if (VisYd < 0.0f)
					{
						wvm(client_dll + dwForceRight, 0); $$$;
						wvm(client_dll + dwForceLeft, 1); $$$;
					}
					else
					{
						wvm(client_dll + dwForceRight, 1); $$$;
						wvm(client_dll + dwForceLeft, 0); $$$;
					}
					VisY = VisYnew; $$$; //set New Y as old Y
				}

				currJumpState = rvm<DWORD>(client_dll + dwForceJump); $$$;
				onGround = rvm<BYTE>(localplayer + fFlags); $$$;
				if (onGround & (1 << 0))
				{ 
					currJumpState |= FORCE_JUMP_BITMASK; $$$;
					wvm(client_dll + dwForceJump, currJumpState); $$$;
				}
				else
				{
					currJumpState &= ~FORCE_JUMP_BITMASK; $$$;
					wvm(client_dll + dwForceJump, currJumpState); $$$;
				}
				Sleep(1); $$$;
			}
			wvm(client_dll + dwForceRight, 0); $$$;
			wvm(client_dll + dwForceLeft, 0); $$$;
		}

		if (cheat(AY_OBFUSCATE("Zoom; Field of View")) == 1 && tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_MENU) < 0) {
			float defsens = stof(getValue(AY_OBFUSCATE("sensitivity"))); $$$;
			SetValue(AY_OBFUSCATE("sensitivity"), defsens / 6); $$$;
			wvm(localplayer + defaultFOV, 15); $$$;
			while (GetAsyncKeyState(VK_MENU) < 0) { Sleep(1); $$$; }
			SetValue(AY_OBFUSCATE("sensitivity"), defsens); $$$;
			wvm(localplayer + defaultFOV, 90); $$$;
		}
		Sleep(1); $$$;
	}
}

void FreeCam();
void Aimbot()
{
	D3DXVECTOR3 newanglez; $$$;
	D3DXVECTOR3 punch, opunch; $$$;
	D3DXVECTOR3 localpos; $$$;
	D3DXVECTOR3 enemycoords; $$$;
	D3DXVECTOR3 currAngles; $$$;
	D3DXVECTOR3 delta; $$$;
	bool aiming = 0; $$$;

	while (true)
	{
		if (tWnd == GetForegroundWindow() && rvm<DWORD>(clientstate + dwClientState_State) == 6)
		{
			if (GetAsyncKeyState(VK_LBUTTON) < 0)
			{
				if (cheat(AY_OBFUSCATE("Aimbot / Friendly Fire")).enabled > 0) {
					if (closest_final) {
						localpos = rvm<D3DXVECTOR3>(localplayer + vecOrigin); $$$;
						localpos.z += rvm<float>(localplayer + vecViewOffset + 0x8); $$$;
						enemycoords = getEntBonePos(rvm<DWORD>(client_dll + dwEntityList + (closest_final - 1) * 0x10), head); $$$;
						newanglez = CalcAngle(localpos, enemycoords); $$$;
						aiming = 1; $$$;
						if (cheat(AY_OBFUSCATE("Recoil Control System")) == 0)
						{
							if (cheat(AY_OBFUSCATE("Smoothing")) != 0) {
								currAngles = rvm<D3DXVECTOR3>(clientstate + dwClientState_ViewAngles); $$$;
								delta = ClampAngle(newanglez - currAngles); $$$;
								newanglez = currAngles + delta / (cheat(AY_OBFUSCATE("Smoothing")).enabled + 1); $$$;
								newanglez = ClampAngle(newanglez); $$$;
							}
							if (!isnan(newanglez.x) && !isnan(newanglez.y))
								wvm<D3DXVECTOR3>(clientstate + dwClientState_ViewAngles, newanglez); $$$;
						}
					}
				}

				if (cheat(AY_OBFUSCATE("Recoil Control System")) == 1)
				{
					if (tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_LBUTTON) < 0)
					{
						punch = rvm<D3DXVECTOR3>(localplayer + aimPunchAngle); $$$;
						punch *= 2; $$$;
						if (aiming)
						{
							newanglez = newanglez - punch; $$$;
						}
						else
						{
							newanglez = rvm<D3DXVECTOR3>(clientstate + dwClientState_ViewAngles); $$$;
						}
						newanglez += (opunch - punch); $$$;
						if (cheat(AY_OBFUSCATE("Smoothing")) != 0) {
							currAngles = rvm<D3DXVECTOR3>(clientstate + dwClientState_ViewAngles); $$$;
							delta = ClampAngle(newanglez - currAngles); $$$;
							newanglez = currAngles + delta / cheat(AY_OBFUSCATE("Smoothing")).enabled; $$$;
							newanglez = ClampAngle(newanglez); $$$;
						}
						if (!isnan(newanglez.x) && !isnan(newanglez.y))
							wvm<D3DXVECTOR3>(clientstate + dwClientState_ViewAngles, newanglez); $$$;
						opunch = punch; $$$;
					}
				}

				if (cheat(AY_OBFUSCATE("Autopistol")) != 0)
				{
					if (isActivePistol()) {
						wvm(client_dll + dwForceAttack, 6); $$$;
						Sleep(15); $$$;
					}
				}
				aiming = 0; $$$;
			}
			else
			{
				if (cheat(AY_OBFUSCATE("Recoil Control System")) == 1)
				{
					opunch = rvm<D3DXVECTOR3>(localplayer + aimPunchAngle); $$$;
					opunch *= 2; $$$;
				}
			}

			
		}
		Sleep(1); $$$;
	}
}

BOOL visible = true;
void Draw() {
	menu(); $$$;
	clientstate = rvm<DWORD>(engine_dll + dwClientState); $$$;
	if (rvm<DWORD>(clientstate + dwClientState_State) == 6) //in server? 
	{
		localplayer = rvm<DWORD>(client_dll + dwLocalPlayer); $$$;
		myteam = rvm<BYTE>(localplayer + iTeamNum); $$$;

		if (cheat(AY_OBFUSCATE("Aimbot / Friendly Fire")).enabled > 0) {
			aimfov = cheat(AY_OBFUSCATE("Aimbot FOV")).enabled * 5; $$$;
			DrawCircle((Width - rightR) / 2, (Height - bottomR) / 2, aimfov, 0, 360, D3DCOLOR_ARGB(50, 255, 255, 0)); $$$;
		}

		if (cheat(AY_OBFUSCATE("Triggerbot")) == 1) {
			who = rvm<BYTE>(localplayer + iCrosshairId); $$$;
			if (who && who < 64) {
				entityList = rvm<DWORD>(client_dll + dwEntityList + (who - 1) * 0x10); $$$;
				who = rvm<BYTE>(entityList + iTeamNum); $$$;

				if (myteam != who)
				{
					INPUT Input = { 0 }; $$$;
					Input.type = INPUT_MOUSE; $$$;
					Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; $$$;
					SendInput(1, &Input, sizeof(INPUT)); $$$;
				}
			}
			else
			{
				INPUT Input = { 0 }; $$$;
				Input.type = INPUT_MOUSE; $$$;
				Input.mi.dwFlags = MOUSEEVENTF_LEFTUP; $$$;
				SendInput(1, &Input, sizeof(INPUT)); $$$;
			}
		}

		if (cheat(AY_OBFUSCATE("ESP & HP Bar & C4timer")) != 0) {
			bombplanted = rvm<bool>(rvm<DWORD>(client_dll + dwGameRulesProxy) + bBombPlanted); $$$; //we have a bomb?
			if (bombplanted)
			{
				if (!bombLine) {
					CreateThread(0, 0, (LPTHREAD_START_ROUTINE)timer, 0, 0, 0); $$$;
					for (i = 0; i <= 4096; i++)
					{
						entityList = rvm<DWORD>(client_dll + dwEntityList + i * 0x10); $$$;
						char ClassName[32]; $$$;
						rvm(rvm<DWORD>(rvm<DWORD>(rvm<DWORD>(rvm<DWORD>(entityList + 0x8) + 0x8) + 0x1) + 0x8) + 0x0, &ClassName); $$$;

						if (_tcsstr(ClassName, _T("PlantedC4")) != NULL)
						{
							printfdbg(AY_OBFUSCATE("PlantedC4 entity %d found\n"), i); $$$;
							c4id = i; $$$;
							break; $$$;
						}
					}
				}
				if (bomb > 0)
				{
					ID3DXFont* pFont; $$$;
					D3DXCreateFont(p_Device, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont); $$$;

					DrawBorderBox(
						(Width - rightR) / 2 - 280 - border,
						(Height - bottomR) / 2 + (Height - bottomR) / 4 - border,
						565,
						40 + border, border, colorprim); $$$;
					DrawFilledRectangle(
						(Width - rightR) / 2 - 280,
						(Height - bottomR) / 2 + (Height - bottomR) / 4,
						(Width - rightR) / 2 - 280 + bombLine,
						(Height - bottomR) / 2 + (Height - bottomR) / 4 + 40, colorsec); $$$;
					DrawString((char*)(std::to_string(bomb).c_str()),
						(Width - rightR) / 2 - 20,
						(Height - bottomR) / 2 + (Height - bottomR) / 4 + 10, 4, D3DCOLOR_XRGB(255, 255, 255), pFont); $$$;

					mycoords = rvm<D3DXVECTOR3>(localplayer + vecOrigin); $$$;
					mycoords.z += rvm<float>(localplayer + vecViewOffset + 0x8); $$$;
					entityList = rvm<DWORD>(client_dll + dwEntityList + c4id * 0x10); $$$;
					coords = rvm<D3DXVECTOR3>(entityList + vecOrigin); $$$;
					delta[2] = mycoords[2] - coords[2]; $$$; deltaXold = mycoords[0] - coords[0]; $$$; deltaYold = mycoords[1] - coords[1]; $$$;
					enemyDistance = sqrtss(deltaXold * deltaXold + deltaYold * deltaYold + delta[2] * delta[2]); $$$;

					float factor = ((enemyDistance - 75.68f) / 789.2f); $$$;
					float rawDamage = 450.7f * (float)exp(factor * -factor); $$$;
					float damage = rawDamage; $$$;

					int ArmorValue = rvm<int>(localplayer + armorVal); $$$;
					if (ArmorValue > 0) {
						float flNew = rawDamage * 0.5f; $$$;
						float flArmor = (rawDamage - flNew) * 0.5f; $$$;

						if (flArmor > static_cast<float>(ArmorValue)) {
							$$$;
							flArmor = static_cast<float>(ArmorValue) * (1.f / 0.5f); $$$;
							flNew = rawDamage - flArmor; $$$;
						}
						damage = flNew; $$$;
					}

					damage = rvm<int>(localplayer + iHealth) - damage; $$$;

					D3DCOLOR dmgcolor;
					if (damage >= 1.0f)
					{
						dmgcolor = D3DCOLOR_XRGB(255, 255, 255); $$$;
					}
					else dmgcolor = D3DCOLOR_XRGB(203, 111, 111); $$$;

					DrawString((char*)(std::to_string(damage).c_str()),
						(Width - rightR) / 2 + 20,
						(Height - bottomR) / 2 + (Height - bottomR) / 4 + 10, 4, dmgcolor, pFont); $$$;

					pFont->Release(); $$$;
				}
			}
		}

		if (cheat(AY_OBFUSCATE("Aimbot / Friendly Fire")) != 0 ||
			cheat(AY_OBFUSCATE("ESP & HP Bar & C4timer")) == 1 ||
			cheat(AY_OBFUSCATE("Spectator List")) != 0
			)
		{
			mycoords = rvm<D3DXVECTOR3>(localplayer + vecOrigin); $$$;
				mycoords.z += rvm<float>(localplayer + vecViewOffset + 0x8); $$$;
				yl_closest = 1000; $$$; xl_closest = 1000; $$$;
				char charint[32]; $$$; int intbuf; $$$; $$$; BYTE lifeState; $$$;
				BYTE speccount = 0; $$$;

				BYTE standingchanged = 0; $$$;
				for (i = 0; i <= 64; i++)
				{
					entityList = rvm<DWORD>(client_dll + dwEntityList + i * 0x10); $$$;

					if (!entityList)
						continue; $$$;

					myid = rvm<BYTE>(clientstate + dwClientState_GetLocalPlayer); $$$;
					if (i == (int)myid)
						continue; $$$;

					lifeState = rvm<BYTE>(entityList + m_lifeState); $$$;
					bDormant = rvm<BYTE>(entityList + bDormantOffset); $$$;

					if (cheat(AY_OBFUSCATE("Spectator List")) == 1 && lifeState && !bDormant)
					{
						spec = rvm<BYTE>(entityList + hObserverTarget); $$$;
						if ((int)spec - 1 == (int)myid)
						{
							speccount++; $$$;
							ID3DXFont* pFont; $$$;
							D3DXCreateFont(p_Device, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont); $$$;
							if (speccount == 1)
								DrawString((char*)AY_OBFUSCATE("Spectating you:"), Width - rightR - 220, (Height - bottomR) / 2, D3DCOLOR_ARGB(100, 255, 255, 255), pFont); $$$;
							rvm(rvm<DWORD>(rvm<DWORD>(rvm<DWORD>(rvm<DWORD>(rvm<DWORD>(engine_dll + dwClientState) + dwClientState_PlayerInfo) + 0x40) + 0xC) + 0x28 + (0x34 * i)) + 0x10, &charint); $$$;
							//UTF8 to UTF16
							intbuf = MultiByteToWideChar(CP_UTF8, 0, charint, -1, NULL, 0); $$$;
							wchar_t* wstr = new wchar_t[intbuf]; $$$;
							MultiByteToWideChar(CP_UTF8, 0, charint, -1, wstr, intbuf); $$$;
							DrawStringW(wstr, Width - rightR - 220, (Height - bottomR) / 2 + speccount * 25, intbuf, colorprim, pFont); $$$;
							delete[] wstr; $$$;
							pFont->Release(); $$$;
						}
					}

					rvm(client_dll + dwViewMatrix, &viewmatrix); $$$;
					coords = rvm<D3DXVECTOR3>(entityList + vecOrigin); $$$;
					coords.z += rvm<float>(localplayer + vecViewOffset + 0x8); $$$;
					team = rvm<BYTE>(entityList + iTeamNum); $$$;
					hp = rvm<DWORD>(entityList + iHealth); $$$;

					if (entityList && !lifeState && hp && !bDormant && WorldToScreen(viewmatrix, coords, &xl, &yl, &wl))
					{
						delta[2] = mycoords[2] - coords[2]; $$$; deltaXold = mycoords[0] - coords[0]; $$$; deltaYold = mycoords[1] - coords[1]; $$$;
						enemyDistance = sqrtss(deltaXold * deltaXold + deltaYold * deltaYold + delta[2] * delta[2]); $$$;

						if ((int)team == 3 && rvm<bool>(entityList + isDefusing))
						{
							color = D3DCOLOR_ARGB(255, 255, 255, 255); $$$;
							go.glowColor = { 255.0f,255,255 }; $$$;
							visible = true; $$$;
						}
						else {
#ifdef BSP_PARSER
							enemyhead = getEntBonePos(rvm<DWORD>(client_dll + dwEntityList + i * 0x10), head); $$$;
#endif
							if ((int)team == (int)myteam)
							{
#ifdef BSP_PARSER
								if (bspParser->is_visible(mycoords, enemyhead)) {
									color = D3DCOLOR_ARGB(255, 0, 255, 255); $$$;
									go.glowColor = { 0,255.0f,255.0f }; $$$;
									visible = true; $$$;
								}
								else {
#endif
									color = D3DCOLOR_ARGB(255, 0, 255, 0); $$$;
									go.glowColor = { 0,255.0f,0 }; $$$;
#ifdef BSP_PARSER
									visible = false; $$$;
								}
#endif
								playercolor.bytes[0] = 0; $$$; playercolor.bytes[1] = 255; $$$; playercolor.bytes[2] = 255; $$$;
							}
							else
							{
#ifdef BSP_PARSER
								if (bspParser->is_visible(enemyhead, mycoords)) {
									color = D3DCOLOR_ARGB(255, 255, 150, 0); $$$;
									go.glowColor = { 3.0f,1.0f,0.0f }; $$$;
									visible = true; $$$;
								}
								else {
#endif
									color = D3DCOLOR_ARGB(255, 255, 0, 0); $$$;
									go.glowColor = { 255.0f,0,0 }; $$$;
#ifdef BSP_PARSER
									visible = false; $$$;
								}
#endif
								playercolor.bytes[0] = 255; $$$; playercolor.bytes[1] = 150; $$$; playercolor.bytes[2] = 0; $$$;
							}
						}

						if (cheat(AY_OBFUSCATE("ESP & HP Bar & C4timer")) == 1)
						{
							DrawBorderBox(xl - 10000 / enemyDistance, yl - 10, 20000 / enemyDistance, 40000 / enemyDistance, 3, color); $$$;
							DrawFilledRectangle(
								xl - 10000 / enemyDistance,
								yl - 15,
								xl - (10000 / enemyDistance) + (20000 / enemyDistance / 100 * hp) + 3,
								yl - 12,
								D3DCOLOR_XRGB(255, 255, 255)); $$$;
						}

						if (cheat(AY_OBFUSCATE("Aimbot / Friendly Fire")) == 1 && (int)team != (int)myteam && visible ||
							cheat(AY_OBFUSCATE("Aimbot / Friendly Fire")) == 2 && visible)
							{
								hyp1 = sqrtss((xl - (Width - rightR) / 2) * (xl - (Width - rightR) / 2) + (yl - (Height - bottomR) / 2) * (yl - (Height - bottomR) / 2)); $$$;
								hyp2 = sqrtss((xl_closest - (Width - rightR) / 2) * (xl_closest - (Width - rightR) / 2) + (yl_closest - (Height - bottomR) / 2) * (yl_closest - (Height - bottomR) / 2)); $$$;

								if (hyp1 < hyp2 && hyp1 < aimfov)
								{
									xl_closest = xl; $$$;
									yl_closest = yl; $$$;
									closest = i; $$$;
								}
							}
					}
				}

			standing = standingchanged; $$$;

			if (xl_closest != 1000) {
				closest_final = closest + 1;
				xl_closest_final = xl_closest - (Width - rightR) / 2;
			}
			else {
				closest_final = 0; $$$;
			}
		}
	}
}

void SkinChanger() {
	int PaintKit = 0; $$$;
	int EntityQuality = 5; $$$;
	float Wear = 0.0001f; $$$;
	int Seed = 0; $$$;
	int StatTrack = 1337; $$$;
	char CustomName[64] = ""; $$$;
	strcat_s(CustomName, AY_OBFUSCATE("Spy1337Hax")); $$$;
	WORD equipment[8] = { 0,0,0,0,0,0,0,0 }; $$$;
	bool equipchanged = true; $$$;
	int gmibncounter = 5000; $$$;
	int knifeID, handsID, knifeIndex = 507; $$$; //karambit

	while (1)
	{
		Sleep(1);
	}

}
void TriggerCheck() {
	while (1) {

		if (cheat.Triggered(AY_OBFUSCATE("Disable All & Close Cheat")))
		{
			cheat(AY_OBFUSCATE("Disable All & Close Cheat")) = 0; $$$;
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DisExit, 0, 0, 0); $$$;
		}

		if (cheat.Triggered(AY_OBFUSCATE("Recoil Control System")))
		{
			if (cheat(AY_OBFUSCATE("Recoil Control System")) == 1)
			{
				$$$;
			}

			cheat.Update(AY_OBFUSCATE("Recoil Control System")); $$$;
		}

		if (rvm<DWORD>(clientstate + dwClientState_State) == 6) {

#ifdef BSP_PARSER
			if (!mapparsed)
			{
				char map[64]; $$$;
				rvm(clientstate + dwClientState_Map, &map); $$$;
				strcat_s(map, AY_OBFUSCATE(".bsp")); $$$;
				if (bspParser->load_map(folder.c_str(), map))
				{
#ifdef DEBUG
					cout << AY_OBFUSCATE("Map parsed!\n");
#endif
					$$$;
				}
				else
				{
#ifdef DEBUG
					cout << AY_OBFUSCATE("Can't parse map\n");
#endif
					$$$;
				}
				mapparsed = true; $$$;
			}
#endif

			if (cheat(AY_OBFUSCATE("Zoom; Field of View")) == 2)
			{
				if (rvm<DWORD>(localplayer + defaultFOV) != 120)
					wvm(localplayer + defaultFOV, 120); $$$;
			}
		}
#ifdef BSP_PARSER
		else {
			if (mapparsed)
				mapparsed = false; $$$;
		}
#endif

		Sleep(1); $$$;
	}
}

void FreeCam() {
	SetValue(AY_OBFUSCATE("cl_forwardspeed"), 0.0f);
	SetValue(AY_OBFUSCATE("cl_sidespeed"), 0.0f);
	SetValue(AY_OBFUSCATE("cl_backspeed"), 0.0f);

	__int64 freeCamOrig1 = rvm<__int64>(client_dll + freeCam); $$$;

	LPVOID Addr = VirtualAllocEx(
		hProcess,
		0,
		sizeof(DWORD),
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	); $$$;

	dword2bytes addr = { (DWORD)Addr }; $$$;
	BYTE shellcode[] = { 0x89, 0x3D, addr.bytes[0], addr.bytes[1], addr.bytes[2], addr.bytes[3], 0xEB, 0x0C }; $$$;

	wvmb(client_dll + freeCam, &shellcode); $$$;
	wvm(client_dll + freeCam + 0xC9, 0x909022EB); $$$;

	float flyangX, flyangY; $$$;

	Sleep(100); $$$;
	DWORD visualOrigin = rvm<DWORD>(DWORD(Addr)); $$$;
	D3DXVECTOR3 vispos = rvm<D3DXVECTOR3>(visualOrigin); $$$;
#ifdef DEBUG
	cout << AY_OBFUSCATE("Free Cam activated, visual position address = 0x") << hex << visualOrigin << "\n"; $$$;
#endif

	wvm<__int64>(client_dll + freeCam, freeCamOrig1); $$$;
	wvm(client_dll + freeCam + 0xC9, 0x07110FF3); $$$;
	SetValue(AY_OBFUSCATE("cl_forwardspeed"), 450.0f); $$$;
	SetValue(AY_OBFUSCATE("cl_sidespeed"), 450.0f); $$$;
	SetValue(AY_OBFUSCATE("cl_backspeed"), 450.0f); $$$;
	VirtualFreeEx(hProcess, Addr, sizeof(DWORD), MEM_RELEASE); $$$;
}

