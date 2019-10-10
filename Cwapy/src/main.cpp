#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <random>
#include <functional>
#include <stdexcept> 
#include "CWTCore.h"

using namespace CWT;

// Suppress MSVC-specific strdup deprecation warning for pybind11.
#define strdup _strdup
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
namespace py = pybind11;


// Open new console for c(in/out/err)
void OpenConsole()
{
	AllocConsole();
	FILE* cinStream;
	FILE* coutStream;
	FILE* cerrStream;
	freopen_s(&cinStream, "CONIN$", "r", stdin);
	freopen_s(&coutStream, "CONOUT$", "w", stdout);
	freopen_s(&cerrStream, "CONOUT$", "w", stderr);
	std::cout.clear();
	std::cin.clear();
	std::cerr.clear();



	/*
	// https://stackoverflow.com/a/57241985:
	// std::wcout, std::wclog, std::wcerr, std::wcin
	HANDLE hConOut = CreateFileW(L"CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hConIn = CreateFileW(L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
	SetStdHandle(STD_ERROR_HANDLE, hConOut);
	SetStdHandle(STD_INPUT_HANDLE, hConIn);
	std::wcout.clear();
	std::wclog.clear();
	std::wcerr.clear();
	std::wcin.clear();
	*/
}

PYBIND11_EMBEDDED_MODULE(cube, m) {
	py::class_<Vector2<int32_t>>(m, "Vector2_int32")
		.def_readwrite("X", &Vector2<int32_t>::X)
		.def_readwrite("Y", &Vector2<int32_t>::Y);

	py::class_<Vector3<int32_t>>(m, "Vector3_int32")
		.def_readwrite("X", &Vector3<int32_t>::X)
		.def_readwrite("Y", &Vector3<int32_t>::Y)
		.def_readwrite("Z", &Vector3<int32_t>::Z);

	py::class_<Vector3<float>>(m, "Vector3_float32")
		.def_readwrite("X", &Vector3<float>::X)
		.def_readwrite("Y", &Vector3<float>::Y)
		.def_readwrite("Z", &Vector3<float>::Z);

	py::class_<Vector3<int64_t>>(m, "Vector3_int64")
		.def_readwrite("X", &Vector3<int64_t>::X)
		.def_readwrite("Y", &Vector3<int64_t>::Y)
		.def_readwrite("Z", &Vector3<int64_t>::Z);

	py::class_<cube::EntityData>(m, "EntityData")
		.def_readwrite("position", &cube::EntityData::position)
		.def_readwrite("rotation", &cube::EntityData::rotation)
		.def_readwrite("velocity", &cube::EntityData::velocity)
		.def_readwrite("accel", &cube::EntityData::accel)
		.def_readwrite("retreat", &cube::EntityData::retreat)
		.def_readwrite("head_rotation", &cube::EntityData::head_rotation)
		.def_readwrite("physics_flags", &cube::EntityData::physics_flags)
		.def_readwrite("hostility_or_ai_type", &cube::EntityData::hostility_or_ai_type)
		.def_readwrite("race", &cube::EntityData::race)
		.def_readwrite("action_id", &cube::EntityData::action_id)
		.def_readwrite("action_timer", &cube::EntityData::action_timer)
		.def_readwrite("combo_hits", &cube::EntityData::combo_hits)
		.def_readwrite("time_since_last_combo_hit", &cube::EntityData::time_since_last_combo_hit)
		//.def_readwrite("appearance", &cube::EntityData::appearance)
		.def_readwrite("binary_toggles", &cube::EntityData::binary_toggles)
		.def_readwrite("roll_time", &cube::EntityData::roll_time)
		.def_readwrite("stun_time", &cube::EntityData::stun_time)
		.def_readwrite("some_animation_time", &cube::EntityData::some_animation_time)
		.def_readwrite("speed_slowed_time", &cube::EntityData::speed_slowed_time)
		.def_readwrite("speed_boosted_time", &cube::EntityData::speed_boosted_time)
		.def_readwrite("level", &cube::EntityData::level)
		.def_readwrite("exp", &cube::EntityData::exp)
		.def_readwrite("job_class", &cube::EntityData::job_class)
		.def_readwrite("specialization", &cube::EntityData::specialization)
		.def_readwrite("camera_looking_at_block_offset", &cube::EntityData::camera_looking_at_block_offset)
		.def_readwrite("hp", &cube::EntityData::hp)
		.def_readwrite("mp", &cube::EntityData::mp)
		.def_readwrite("stealth", &cube::EntityData::stealth)
		.def_readwrite("current_movement_type_speed", &cube::EntityData::current_movement_type_speed)
		.def_readwrite("light_diameter", &cube::EntityData::light_diameter)
		.def_readwrite("eagle_flying_to_zone_pos", &cube::EntityData::eagle_flying_to_zone_pos)
		.def_readwrite("eagle_flying_from_coords", &cube::EntityData::eagle_flying_from_coords)
		//.def_readwrite("some_unk_item", &cube::EntityData::some_unk_item)
		//.def_readwrite("worn_equipment", &cube::EntityData::worn_equipment)
		//.def_readwrite("name", &cube::EntityData::name)
		.def("get_name", [](const cube::EntityData& e) {return std::string(e.name);})
		.def_readwrite("client_steam_ID", &cube::EntityData::client_steam_ID);


	py::class_<cube::Creature>(m, "Creature")
		.def_readwrite("entity_data", &cube::Creature::entity_data);

	py::class_<cube::World>(m, "World")
		.def_readwrite("local_player", &cube::World::local_player, py::return_value_policy::reference)
		.def_readwrite("creatures_list", &cube::World::creatures_list, py::return_value_policy::reference);
		

	py::class_<cube::Game>(m, "Game")
		.def_readwrite("seed", &cube::Game::seed)
		.def_readonly("world", &cube::Game::world, py::return_value_policy::reference);

	m.def("get_game", &CWT::GetGamePtr, py::return_value_policy::reference);
}

DWORD WINAPI MyFunc(LPVOID lpvParam) 
{
	OpenConsole();

	// Wait until cube::Game is initialized.
	cube::Game* game = nullptr;
	while (game == nullptr) {
		game = CWT::GetGamePtr();
		Sleep(250);
	}

	// Set the local player HP.
	game->world->local_player->entity_data.hp = 500;

	std::cout << "Got game" << std::endl;

	// Create our python interpreter.
	py::initialize_interpreter();

	while (true) {
		// Run script.py if the user is pressing the Y key.
		if (GetAsyncKeyState((int)'Y') & 0x8000) {
			std::cout << "Running Python script!" << std::endl;
			try {
				py::eval_file("script.py");
			}
			catch (std::exception const& e) {
				std::cout << e.what() << std::endl;

			}
			Sleep(2000);
		}
		Sleep(250);
	}

	// Close our python interpreter.
	py::finalize_interpreter();

	return 0;
};

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, MyFunc, 0, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}