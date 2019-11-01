#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <random>
#include <functional>
#include <stdexcept> 
#include <algorithm>
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

	py::class_<cube::Item>(m, "Item")
		.def_readwrite("category", &cube::Item::category)
		.def_readwrite("id", &cube::Item::id)
		.def_readwrite("model", &cube::Item::model)
		.def_readwrite("region_x", &cube::Item::region_x)
		.def_readwrite("region_y", &cube::Item::region_y)
		.def_readwrite("stars", &cube::Item::stars)
		.def_readwrite("field_18", &cube::Item::field_18)
		.def_readwrite("material", &cube::Item::material)
		//.def_readwrite("customizations", &cube::Item::customizations)
		.def_readwrite("customization_count", &cube::Item::customization_count)
		.def_readwrite("field_9E", &cube::Item::field_9E)
		.def_readwrite("field_9F", &cube::Item::field_9F);

	py::class_<cube::WornEquipment>(m, "WornEquipment")
		.def_readwrite("mystery_near_neck", &cube::WornEquipment::mystery_near_neck)
		.def_readwrite("neck", &cube::WornEquipment::neck)
		.def_readwrite("chest", &cube::WornEquipment::chest)
		.def_readwrite("feet", &cube::WornEquipment::feet)
		.def_readwrite("hands", &cube::WornEquipment::hands)
		.def_readwrite("shoulder", &cube::WornEquipment::shoulder)
		.def_readwrite("weapon_left", &cube::WornEquipment::weapon_left)
		.def_readwrite("weapon_right", &cube::WornEquipment::weapon_right)
		.def_readwrite("ring_left", &cube::WornEquipment::ring_left)
		.def_readwrite("ring_right", &cube::WornEquipment::ring_right)
		.def_readwrite("pet", &cube::WornEquipment::pet);

	py::class_<cube::EntityData::Appearance>(m, "Appearance")
		.def_readwrite("hair_color_r", &cube::EntityData::Appearance::hair_color_r)
		.def_readwrite("hair_color_g", &cube::EntityData::Appearance::hair_color_g)
		.def_readwrite("hair_color_b", &cube::EntityData::Appearance::hair_color_b)
		.def_readwrite("movement_flags", &cube::EntityData::Appearance::movement_flags)
		.def_readwrite("graphical_size", &cube::EntityData::Appearance::graphical_size)
		.def_readwrite("hitbox_size", &cube::EntityData::Appearance::hitbox_size)
		.def_readwrite("physical_size", &cube::EntityData::Appearance::physical_size)
		.def_readwrite("face_id", &cube::EntityData::Appearance::face_id)
		.def_readwrite("hair_id", &cube::EntityData::Appearance::hair_id)
		.def_readwrite("hands_id", &cube::EntityData::Appearance::hands_id)
		.def_readwrite("feet_id", &cube::EntityData::Appearance::feet_id)
		.def_readwrite("chest_id", &cube::EntityData::Appearance::chest_id)
		.def_readwrite("tail_id", &cube::EntityData::Appearance::tail_id)
		.def_readwrite("shoulder_id", &cube::EntityData::Appearance::shoulder_id)
		.def_readwrite("wings_id", &cube::EntityData::Appearance::wings_id)
		.def_readwrite("head_scale", &cube::EntityData::Appearance::head_scale)
		.def_readwrite("chest_scale", &cube::EntityData::Appearance::chest_scale)
		.def_readwrite("hand_scale", &cube::EntityData::Appearance::hand_scale)
		.def_readwrite("feet_scale", &cube::EntityData::Appearance::feet_scale)
		.def_readwrite("unk_scale", &cube::EntityData::Appearance::unk_scale)
		.def_readwrite("weapon_scale", &cube::EntityData::Appearance::weapon_scale)
		.def_readwrite("tail_scale", &cube::EntityData::Appearance::tail_scale)
		.def_readwrite("shoulder_scale", &cube::EntityData::Appearance::shoulder_scale)
		.def_readwrite("wings_scale", &cube::EntityData::Appearance::wings_scale)
		.def_readwrite("maybe_chest_rotation", &cube::EntityData::Appearance::maybe_chest_rotation)
		.def_readwrite("hands_rotation", &cube::EntityData::Appearance::hands_rotation)
		.def_readwrite("wings_rotation", &cube::EntityData::Appearance::wings_rotation)
		.def_readwrite("chest_position", &cube::EntityData::Appearance::chest_position)
		.def_readwrite("head_position", &cube::EntityData::Appearance::head_position)
		.def_readwrite("hands_position", &cube::EntityData::Appearance::hands_position)
		.def_readwrite("feet_position", &cube::EntityData::Appearance::feet_position)
		.def_readwrite("unk_position", &cube::EntityData::Appearance::unk_position)
		.def_readwrite("wings_position", &cube::EntityData::Appearance::wings_position);

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
		.def_readwrite("appearance", &cube::EntityData::appearance)
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
		.def_readwrite("some_unk_item", &cube::EntityData::some_unk_item)
		.def_readwrite("worn_equipment", &cube::EntityData::worn_equipment)
		.def_property("name",
			[](const cube::EntityData& e) -> std::string { // getter
				return std::string(e.name);
			},
			[](cube::EntityData& e, const std::string& name) { // setter
				std::memcpy(e.name, name.c_str(), 16);
				e.name[15] = '\x00';
			}
		)
		.def_readwrite("client_steam_ID", &cube::EntityData::client_steam_ID);


	py::class_<cube::Creature>(m, "Creature")
		.def_static("new", [](uint64_t guid)
			{
				uint64_t tmp_guid = guid;
				return cube::Creature::New(&tmp_guid);
			},
			py::return_value_policy::reference
		)
		.def_readwrite("guid", &cube::Creature::guid)
		.def_readwrite("entity_data", &cube::Creature::entity_data)
		.def_readwrite("buffs", &cube::Creature::buffs, py::return_value_policy::reference)
		.def_readwrite("character_height_bob", &cube::Creature::character_height_bob)
		.def_readwrite("on_damage_flash_effect", &cube::Creature::on_damage_flash_effect)
		.def_readwrite("stamina", &cube::Creature::stamina)
		.def_readwrite("pet_guid", &cube::Creature::pet_guid)
		//.def_readwrite("inventories", &cube::Creature::inventories)
		.def_readwrite("entity_data", &cube::Creature::entity_data)
		.def_readwrite("unk_item", &cube::Creature::unk_item)
		.def_readwrite("gold", &cube::Creature::gold)
		.def_readwrite("climbing_speed", &cube::Creature::climbing_speed)
		.def_readwrite("swimming_speed", &cube::Creature::swimming_speed)
		.def_readwrite("diving_skill", &cube::Creature::diving_skill)
		.def_readwrite("riding_speed", &cube::Creature::riding_speed)
		.def_readwrite("hang_gliding_speed", &cube::Creature::hang_gliding_speed)
		.def_readwrite("sailing_speed", &cube::Creature::sailing_speed)
		.def_readwrite("light_diameter", &cube::Creature::light_diameter);

		//.def_readwrite("animation_state", &cube::Creature::animation_state)


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
	std::cout << "Opened console" << std::endl;
	CWT::InitCWT();

	// Wait until cube::Game is initialized.
	cube::Game* game = nullptr;
	while (game == nullptr) {
		game = CWT::GetGamePtr();
		Sleep(250);
	}

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