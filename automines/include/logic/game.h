#pragma once

namespace logic {
	class Game {
	public:
		class GameObserver {

		};

		class PlayingField {
		public:
			enum class Tiles {
				UNINITIALIZED = -2,
				UNKNOWN = -1,
				EMPTY = 0,
				NEIGHBOUR_1_MINE = 1,
				NEIGHBOUR_2_MINE = 2,
				NEIGHBOUR_3_MINE = 3,
				NEIGHBOUR_4_MINE = 4,
				NEIGHBOUR_5_MINE = 5,
				NEIGHBOUR_6_MINE = 6,
				NEIGHBOUR_7_MINE = 7,
				NEIGHBOUR_8_MINE = 8,
				IS_MINE = 9
			};
		};
	};
}