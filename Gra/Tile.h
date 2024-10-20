#include "Sprite.h"

class Tile
{
public:
	enum class TileType : int
	{
		Empty = 0,
		Wall = 1,
		Floor = 2,
		Stairs_down = 3,
		Stairs_up = 4,
		River = 5,
    };

	enum class Visibility : int
	{
		Visible = 0,
		Seen = 1,
		Never_seen = 2,
	};

	Tile();
	void setType(TileType);
	void setVisibility(Visibility);
	bool collision;
	Color original_color;
	TileType tile_type = TileType::Empty;
	Visibility visibility = Visibility::Never_seen;
	Sprite sprite;
};

