#include "../include/tile_layer_renderer.hpp"
#include "../include/tile_layer.hpp"
#include "../include/map.hpp"
#include "../include/game.hpp"
#include <xd/system.hpp>
#include <xd/graphics.hpp>


// TODO: Support multiple tilesets
void Tile_Layer_Renderer::render(Map& map) {
    if (!layer.visible)
        return;
    if (needs_redraw) {
        batch.clear();
        for (int y = 0; y < map.get_height(); ++y) {
            for (int x = 0; x < map.get_width(); ++x) {
                int i = y * map.get_width() + x;
                const Tileset& tileset = map.get_tileset(0);
                int tile_id = static_cast<const Tile_Layer&>(layer).tiles[i];
                if (tile_id > 0) {
                    int tile_index = tile_id - tileset.first_id;
                    xd::rect src = tileset.tile_source_rect(tile_index);
                    float tile_x = static_cast<float>(x * map.get_tile_width());
                    float tile_y = static_cast<float>(y * map.get_tile_height());
                    xd::vec4 color(1.0f, 1.0f, 1.0f, layer.opacity);
                    batch.add(tileset.image_texture, src, tile_x, tile_y, color);
                }
            }
        }
        cache = batch.create_batches();
        needs_redraw = false;
    }
    batch.draw(map.get_game().get_mvp(), cache, map.get_game().ticks());
}
