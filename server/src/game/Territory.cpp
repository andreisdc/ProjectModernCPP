#pragma once

#include <array>

#include "Territory.hpp"

static std::array<std::string, 9> vec3x3 = {
		"Satu Mare",
		"Maramures",
		"Moldova",
		"Timisoara",
		"Ardeal",
		"Transilvania",
		"Oltenia",
		"Muntenia",
		"Dobrogea",
};

static std::array<std::string, 15> vec5x3 = {
		"Satu Mare",
		"Maramures",
		"Iasi",
		"Timisoara",
		"Cluj",
		"Transilvania",
		"Brasov",
		"Galati",
		"Banat",
		"Oltenia",
		"Teleorman",
		"Bucuresti",
		"Calarasi",
		"Tulcea",
		"Constanta",
};

static std::array<std::string, 24> vec6x4 = {
		"Satu Mare",
		"Maramures",
		"Suceava",
		"Botosani",
		"Bihor",
		"Cluj2",
		"Cluj",
		"Harghita",
		"Iasi",
		"Arad",
		"Banat",
		"Hunedoara",
		"Alba",
		"Sibiu",
		"Brasov",
		"Galati",
		"Caras Sevarin",
		"Mehedinti",
		"Teleorman",
		"Bucuresti",
		"Braila",
		"Calarasi",
		"Tulcea",
		"Constanta",
};

std::vector<Territory *> Territory::generate_territories(int player_count) {
	std::vector<Territory *> v;

	if (player_count == 2) {
		int i = 0;
		for (const auto &name: vec3x3) {
			auto territory = new Territory;
			territory->id = i;
			territory->name = name;
			v.push_back(territory);
			i++;
		}
	} else if (player_count == 3) {
		int i = 0;
		for (const auto &name: vec5x3) {
			auto territory = new Territory;
			territory->id = i;
			territory->name = name;
			v.push_back(territory);
			i++;
		}
	} else if (player_count == 4) {
		int i = 0;
		for (const auto &name: vec6x4) {
			auto territory = new Territory;
			territory->id = i;
			territory->name = name;
			v.push_back(territory);
			i++;
		}
	} else {
		throw std::exception("Invalid amount of players for generating territories!");
	}

	return v;
}
