#include "main.h"
#include <thread>

int aim_key = VK_RBUTTON;
int aim_close_key = VK_XBUTTON1;
bool aim_close_key_b = false;
int aim_headshot_key = VK_XBUTTON2;
bool aim_headshot_key_b = false;
int alt_aim_key = 0x37;
bool active = true;
bool ready = false;
int offset_mem = 1; 
bool aiming = false; 
uint64_t g_Base = 0; 
float max_dist = 300.0f * 40.0f;

uint64_t add[14];

bool th_true = true;

bool firingrange_pressed = false;
bool firingrange = false;

bool allies = false;
bool allies_pressed_key_F8_pressed = false;

bool item_glow = false;
bool item_glow_key_F7_pressed = false;

int recoil_level = 2;
float recoil_level_float = 0.25f;
bool recoil_level_key_F6_pressed = false;

int recoil_control = 1;
bool recoil_control_key_F5_pressed = false;

int cqc_fov = 5;
float cqc_fov_level = 50;
bool cqc_fov_key_F3_pressed = false;

int cqc_smooth = 7;
int cqc_smooth_level = 70;
bool cqc_smooth_key_F4_pressed = false;

int aim = 2;
bool aim_key_pressed = false; 

int smooth = 80;
int smooth_old;
bool smooth_key_NUM9_pressed = false;
bool smooth_key_NUM7_pressed = false; 

float fov = 5.0f;
float fov_old;
bool fov_key_4_pressed = false; 
bool fov_key_6_pressed = false; 


int bone = 7;
int bone_old;
bool bone_key_1_pressed = false; 
bool bone_key_3_pressed = false;


int player_glow = 1;
bool playerglow_pressed = 0;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

void DisplayTerm()
{
	system("Color 04");
	std::cout << R"(
                        ___                     _                               _
                       / _ \                   | |                             | |
                      / /_\ \_ __   _____  __  | |     ___  __ _  ___ _ __   __| |___
                      |  _  | '_ \ / _ \ \/ /  | |    / _ \/ _` |/ _ \ '_ \ / _` / __|
                      | | | | |_) |  __/>  <   | |___|  __/ (_| |  __/ | | | (_| \__ \
                      \_| |_/ .__/ \___/_/\_\  \_____/\___|\__, |\___|_| |_|\__,_|___/
                            | |                             __/ |
                            |_|                            |___/
		)" << '\n';

	std::cout << " COMMON                                                OTHER                                       " << std::endl;
	std::cout << " -------------------------------------------------     --------------------------------------------------" << std::endl;
	std::cout << " Aimbot            Numpad -            [     ]         Recoil Control    F5                  [     ]" << std::endl;
	std::cout << " Smooth            Numpad 7/9          [      ]        Recoil Level      F6                  [       ]" << std::endl;
	std::cout << " Fov               Numpad 4/6          [      ]        Item Glow         F7                  [     ]" << std::endl;
	std::cout << " Bone              Numpad 1/3          [     ]         Target Allies     F8                  [     ]" << std::endl;
	std::cout << " Player Glow       Numpad *            [     ]         Firing Range      F9                  [     ]" << std::endl;
	std::cout << " Max Distance      Arrows LEFT/RIGHT   [         ]     CQC Fov           F3                  [      ]" << std::endl;
	std::cout << " CQC Aimbot        MOUSE BUTTON 1      [     ]         CQC Smooth        F4                  [      ]" << std::endl;
	std::cout << " Headshot Aimbot   MOUSE BUTTON 2      [     ]         Apex                                  [ V2.3 ]" << std::endl;
	std::cout << " -------------------------------------------------     --------------------------------------------------" << std::endl;
	printf(XorStr(" add_addr: 0x%I64x\n"), (uint64_t)&add[0] - (uint64_t)GetModuleHandle(NULL));

	if (active)
	{
		ready = true;
		printf(XorStr("\n Ready\n"));
	}

    ShowConsoleCursor(false);

	while (th_true) {
        gotoxy(41, 12); // aim
		std::cout << (char)32;
		std::cout << std::to_string(aim);

        gotoxy(95, 12); // recoil control
        std::cout << (char)32;
        std::cout << std::to_string(recoil_control);

        gotoxy(41, 13); // smooth
		std::cout << (char)32;
		std::cout << std::to_string(smooth);

        gotoxy(95, 13); // recoil level
        std::cout << (char)32;
        std::cout << std::to_string(recoil_level) << "0%";

        gotoxy(43, 14); // fov
		std::cout << (char)32;
        gotoxy(41, 14); 
		std::cout << (char)32;
		std::cout << std::trunc(fov);

        gotoxy(95, 14); // item glow
        std::cout << (char)32;
        std::cout << std::to_string(item_glow);

        gotoxy(43, 15); // bone
		std::cout << (char)32;
        gotoxy(41, 15);
		std::cout << (char)32;
		std::cout << std::to_string(bone);

        gotoxy(95, 15); // allies
        std::cout << (char)32;
        std::cout << std::to_string(allies);

        gotoxy(41, 16); // player glow
		std::cout << (char)32;
		std::cout << std::to_string(player_glow);

        gotoxy(95, 16); // firingrange
        std::cout << (char)32;
        std::cout << std::to_string(firingrange);

        gotoxy(42, 17); // max dist
		std::cout << (char)32;
        gotoxy(43, 17);
		std::cout << (char)32;
        gotoxy(44, 17);
		std::cout << (char)32;
        gotoxy(45, 17);
		std::cout << (char)32;
        gotoxy(46, 17);
		std::cout << (char)32;
        gotoxy(41, 17);
		std::cout << (char)32;
		std::cout << std::trunc(max_dist);

        gotoxy(95, 17); // cqc fov
        std::cout << (char)32;
        std::cout << std::to_string(cqc_fov) << "0";

        gotoxy(43, 18); // aim close button
		std::cout << (char)32;
        gotoxy(41, 18);
		std::cout << (char)32;
		std::cout << std::to_string(aim_close_key_b);

        gotoxy(95, 18); // cqc smooth
        std::cout << (char)32;
        std::cout << std::to_string(cqc_smooth) << "0";

        gotoxy(43, 19); // headshot button
		std::cout << (char)32;
        gotoxy(41, 19);
		std::cout << (char)32;
		std::cout << std::to_string(aim_headshot_key_b);

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	th_true = false;
}

bool IsKeyDown(int vk) {
    return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

int main(int argc, char** argv) {
    add[0] = (uintptr_t)&offset_mem;
    add[1] = (uintptr_t)&aim;
    add[2] = (uintptr_t)&fov;
    add[3] = (uintptr_t)&aiming;
    add[4] = (uintptr_t)&g_Base;
    add[5] = (uintptr_t)&max_dist;
    add[6] = (uintptr_t)&player_glow;
    add[7] = (uintptr_t)&smooth;
    add[8] = (uintptr_t)&bone;
    add[9] = (uintptr_t)&recoil_control;
    add[10] = (uintptr_t)&recoil_level_float;
    add[11] = (uintptr_t)&item_glow;
    add[12] = (uintptr_t)&allies;
    add[13] = (uintptr_t)&firingrange;

    std::thread first(DisplayTerm);

    while (active) {
        if (IsKeyDown(VK_MULTIPLY) && playerglow_pressed == 0) // PLAYER GLOW
        {
            playerglow_pressed = 1;
            switch (player_glow) {
            case 0:
                player_glow = 1; 
                break;
            case 1:
                player_glow = 0; 
                break;
            default:
                break;
            }
        }
        else if (!IsKeyDown(VK_MULTIPLY) && playerglow_pressed == 1)
        {
            playerglow_pressed = 0;
        }

        if (IsKeyDown(VK_F5) && recoil_control_key_F5_pressed == 0) // RECOIL CONTROL
        {
            recoil_control_key_F5_pressed = 1;
            switch (recoil_control) {
            case 0:
                recoil_control = 1; 
                break;
            case 1:
                recoil_control = 2; 
                break;
            case 2:
                recoil_control = 0; 
                break;
            default:
                break;
            }
        }
        else if (!IsKeyDown(VK_F5) && recoil_control_key_F5_pressed == 1) 
        {
            recoil_control_key_F5_pressed = 0;
        }

        if (IsKeyDown(VK_F6) && recoil_level_key_F6_pressed == 0)  // RECOIL LEVEL
        {
            recoil_level_key_F6_pressed = 1;
            switch (recoil_level) {
            case 1:
                recoil_level = 2;
                recoil_level_float = 0.20f;
                break;
            case 2:
                recoil_level = 3;
                recoil_level_float = 0.30f;
                break;
            case 3:
                recoil_level = 4;
                recoil_level_float = 0.40f;
                break;
            case 4:
                recoil_level = 5;
                recoil_level_float = 0.50f;
                break;
            case 5:
                recoil_level = 6;
                recoil_level_float = 0.60f;
                break;
            case 6:
                recoil_level = 1;
                recoil_level_float = 0.10f;
                break;

            default:
                break;
            }
        }
        else if (!IsKeyDown(VK_F6) && recoil_level_key_F6_pressed == 1) 
        {
            recoil_level_key_F6_pressed = 0;
        }

        if (IsKeyDown(VK_SUBTRACT) && aim_key_pressed == 0) // AIMBOT
        {
            aim_key_pressed = 1;
            switch (aim) {
            case 0:
                aim = 1; 
                break;
            case 1:
                aim = 2;
                break;
            case 2:
                aim = 0; 
                break;
            default:
                break;
            }
        }
        else if (!IsKeyDown(VK_SUBTRACT) && aim_key_pressed == 1) 
        {
            aim_key_pressed = 0;
        }

        if (IsKeyDown(VK_F7) && item_glow_key_F7_pressed == 0) // ITEM GLOW
        {
            item_glow_key_F7_pressed = 1;
            item_glow = !item_glow;
        }
        else if (!IsKeyDown(VK_F7) && item_glow_key_F7_pressed == 1) 
        {
            item_glow_key_F7_pressed = 0; 
        }

        if (IsKeyDown(VK_F8) && allies_pressed_key_F8_pressed == 0) // ALLIES
        {
            allies_pressed_key_F8_pressed = 1;
            allies = !allies;
        }
        else if (!IsKeyDown(VK_F8) && allies_pressed_key_F8_pressed == 1) 
        { 
            allies_pressed_key_F8_pressed = 0; 
        }

        if (IsKeyDown(VK_F9) && firingrange_pressed == 0) // FIRINGRANGE
        {
            firingrange_pressed = 1;
            firingrange = !firingrange;
        }
        else if (!IsKeyDown(VK_F9) && firingrange_pressed == 1) 
        {
            firingrange_pressed = 0; 
        }

        if (IsKeyDown(VK_F4) && cqc_smooth_key_F4_pressed == 0) // SMOOTH LEVEL
        {
            cqc_smooth_key_F4_pressed = 1;
            switch (cqc_smooth) {
            case 1:
                cqc_smooth = 2; 
                cqc_smooth_level = 20;
                break;
            case 2:
                cqc_smooth = 3; 
                cqc_smooth_level = 30;
                break;
            case 3:
                cqc_smooth = 4; 
                cqc_smooth_level = 40;
                break;
            case 4:
                cqc_smooth = 5;
                cqc_smooth_level = 50;
                break;
            case 5:
                cqc_smooth = 6; 
                cqc_smooth_level = 60;
                break;
            case 6:
                cqc_smooth = 7; 
                cqc_smooth_level = 70;
                break;
            case 7:
                cqc_smooth = 1; 
                cqc_smooth_level = 10;
                break;
            default:
                break;
            }
        }
        else if (!IsKeyDown(VK_F4) && cqc_smooth_key_F4_pressed == 1)  
        {
            cqc_smooth_key_F4_pressed = 0;
        }

        if (IsKeyDown(VK_NUMPAD9) && smooth_key_NUM9_pressed == 0) // SMOOTH ADD
        {
            smooth_key_NUM9_pressed = 1;
            smooth += 1;
            if (smooth > 100) smooth = 100;
        }
        else if (!IsKeyDown(VK_NUMPAD9) && smooth_key_NUM9_pressed == 1) 
        {
            smooth_key_NUM9_pressed = 0;
        }

        if (IsKeyDown(VK_NUMPAD7) && smooth_key_NUM7_pressed == 0) // SMOOTH REMOVE
        {
            smooth_key_NUM7_pressed = 1;
            smooth -= 1;
            if (smooth < 20) smooth = 20;
        }
        else if (!IsKeyDown(VK_NUMPAD7) && smooth_key_NUM7_pressed == 1) 
        {
            smooth_key_NUM7_pressed = 0;
        }

        if (IsKeyDown(VK_F3) && cqc_fov_key_F3_pressed == 0) // FOV LEVEL
        {
            cqc_fov_key_F3_pressed = 1;
            switch (cqc_fov) {
            case 1:
                cqc_fov = 2;
                cqc_fov_level = 20;
                break;
            case 2:
                cqc_fov = 3;
                cqc_fov_level = 30;
                break;
            case 3:
                cqc_fov = 4;
                cqc_fov_level = 40;
                break;
            case 4:
                cqc_fov = 5;
                cqc_fov_level = 50;
                break;
            case 5:
                cqc_fov = 6;
                cqc_fov_level = 60;
                break;
            case 6:
                cqc_fov = 7;
                cqc_fov_level = 70;
                break;
            case 7:
                cqc_fov = 1;
                cqc_fov_level = 10;
                break;

            default:
                break;
            }
        }
        else if (!IsKeyDown(VK_F3) && cqc_fov_key_F3_pressed == 1)
        {
            cqc_fov_key_F3_pressed = 0;
        }

        if (IsKeyDown(VK_NUMPAD6) && fov_key_4_pressed == 0) // FOV ADD
        {
            fov_key_4_pressed = 1;
            fov += 1;
            if (fov > 100) fov = 100;
        }
        else if (!IsKeyDown(VK_NUMPAD6) && fov_key_4_pressed == 1) 
        {
            fov_key_4_pressed = 0;
        }

        if (IsKeyDown(VK_NUMPAD4) && fov_key_6_pressed == 0) // FOV REMOVE
        {
            fov_key_6_pressed = 1;
            fov -= 1;
            if (fov < 1) fov = 1;
        }
        else if (!IsKeyDown(VK_NUMPAD4) && fov_key_6_pressed == 1) 
        {
            fov_key_6_pressed = 0;
        }

        if (IsKeyDown(VK_NUMPAD3) && bone_key_1_pressed == 0) // BONE ADD
        {
            bone_key_1_pressed = 1;
            bone += 1;
            if (bone > 100) bone = 100;
        }
        else if (!IsKeyDown(VK_NUMPAD3) && bone_key_1_pressed == 1) 
        {
            bone_key_1_pressed = 0;
        }

        if (IsKeyDown(VK_NUMPAD1) && bone_key_3_pressed == 0) // BONE REMOVE
        {
            bone_key_3_pressed = 1;
            bone -= 1;
            if (bone < 1) bone = 1;
        }
        else if (!IsKeyDown(VK_NUMPAD1) && bone_key_3_pressed == 1) 
        {
            bone_key_3_pressed = 0;
        }

        if (IsKeyDown(VK_LEFT)) 
        {
            if (max_dist > 100.0f * 40.0f) 
                max_dist -= 50.0f * 40.0f; // move by 2,000f
        }

        if (IsKeyDown(VK_RIGHT)) 
        {
            if (max_dist < 800.0f * 40.0f) 
                max_dist += 50.0f * 40.0f; // move by 2,000f
        }

        if (IsKeyDown(aim_close_key) && !aim_close_key_b) // CQC MODE ON
        {
            fov_old = fov;
            fov = cqc_fov_level;
            smooth_old = smooth;
            smooth = cqc_smooth_level;
            aim_close_key_b = true;
        }
        else if (!IsKeyDown(aim_close_key) && aim_close_key_b) // CQC MODE OFF
        {
            fov = fov_old;
            smooth = smooth_old;
            aim_close_key_b = false;
        }

        if (IsKeyDown(aim_headshot_key) && !aim_headshot_key_b) // HEADSHOT MODE ON
        {
            bone_old = bone;
            bone = 8;
            aim_headshot_key_b = true;
        }
        else if (!IsKeyDown(aim_headshot_key) && aim_headshot_key_b) // HEADSHOT MODE OFF
        {
            bone = bone_old;
            aim_headshot_key_b = false;
        }

        if (IsKeyDown(aim_key) || IsKeyDown(aim_close_key)) // TOGGLE AIMING
        {
            aiming = true;
        }
        else {
            aiming = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    ready = false;
    return 0;
}
