#pragma once
#include "ant.hpp"
#include "world.hpp"


struct SoldierUpdater
{
	static void update(Ant& ant, World& world, float dt)
	{
		WorldCell& cell = world.map.get(ant.position);
		cell.addPresence();
		ant.direction_update.update(dt);
		if (ant.direction_update.ready()) {
			ant.direction_update.reset();
			findMarker(ant, world);
		}
	}

	static void findMarker(Ant& ant, World& world)
	{
		// Init
		SamplingResult result;
		result.max_direction = ant.direction.getVec();
		const Mode marker_phase = ant.getMarkersSamplingType();
		const float sample_angle_range = PI * 0.7f;
		const float current_angle = getAngle(result.max_direction);
		const float fight_dist = 10.0f;

		ant.fight_request.active = false;

		// Sample the world
		const uint32_t sample_count = 64;
		for (uint32_t i(sample_count); i--;) {
			// Get random point in range
			const float sample_angle = current_angle + RNGf::getRange(sample_angle_range);
			const float distance = RNGf::getUnder(ant.marker_detection_max_dist);
			const sf::Vector2f to_marker(cos(sample_angle), sin(sample_angle));
			auto* cell = world.map.getSafe(ant.position + distance * to_marker);
			const HitPoint hit_result = world.map.getFirstHit(ant.position, to_marker, distance);
			// Check cell
			if (!cell || hit_result.cell) {
				if (hit_result.cell) {
					hit_result.cell->discovered = 1.0f;
				}
				continue;
			}
			cell->discovered += 0.1f;
			// Check for food or colony
			if (cell->isPermanent(ant.col_id) && (marker_phase == Mode::ToHome)) {
				result.max_direction = to_marker;
				result.found_permanent = true;
				break;
			}
			// Check for close enemy
			if (distance < ant.length) {
				const AntRef enemy = cell->getEnemy(ant.col_id);
				if (enemy.active) {
					ant.request_fight(enemy);
					return;
				}
			}
			// Check for enemy
			if (cell->checkFight(ant.col_id)) {
				result.found_fight = true;
				result.max_direction = to_marker;
				ant.detectEnemy();
				break;
			}
			// Flee if repellent
			if (cell->getRepellent(ant.col_id) > result.max_repellent) {
				result.max_repellent = cell->getRepellent(ant.col_id);
				result.repellent_cell = cell;
			}
			// Check for the most intense marker
			const float marker_intensity = to<float>(cell->getIntensity(marker_phase, ant.col_id) * std::pow(cell->wall_dist, 2.0));
			if (marker_intensity > result.max_intensity) {
				result.max_intensity = marker_intensity;
				result.max_direction = to_marker;
				result.max_cell = cell;
			}
		}
		// Process sampling result
		if (result.found_fight) {
			ant.direction = getAngle(result.max_direction);
			ant.fight_mode = FightMode::ToFight;
			return;
		}
		// Update direction
		if (result.max_intensity) {
			ant.direction = getAngle(result.max_direction);
		}
	}
};
