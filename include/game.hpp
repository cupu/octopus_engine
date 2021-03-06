#ifndef HPP_GAME
#define HPP_GAME

#include <vector>
#include <memory>
#include <string>
#include <xd/system.hpp>
#include <xd/graphics/types.hpp>
#include <xd/graphics/simple_text_renderer.hpp>
#include <xd/graphics/font.hpp>
#include <xd/audio.hpp>
#include "direction.hpp"

class Camera;
class Map;
class Map_Object;
class Scripting_Interface;
class Canvas;
class NPC;
class Clock;
class Save_File;
namespace xd {
    class shader_program;
    class asset_manager;
}

class Game {
public:
    Game(bool editor_mode = false);
    ~Game();
    // Main game loop
    void run();
    // Logic update
    void frame_update();
    // Render the scene
    void render();
    // Pause game
    void pause();
    // Resume game
    void resume();
    // Window width
    int width() const {
        return window ? window->framebuffer_width() : 1;
    }
    // Window height
    int height() const {
        return window ? window->framebuffer_height() : 1;
    }
    // Manually set window size (for editor)
    void set_size(int width, int height);
    // Frames per seconds
    int fps() const {
        return window->fps();
    }
    // Number of frames since the beginning
    int frame_count() const {
        return window->frame_count();
    }
    // Is key currently pressed
    bool pressed(const xd::key& key, int modifiers = 0) const {
        return window->pressed(key, modifiers);
    }
    bool pressed(const std::string& key, int modifiers = 0) const {
        return window->pressed(key, modifiers);
    }
    // Was key triggered since last update?
    bool triggered(const xd::key& key, int modifiers = 0) const {
        return window->triggered(key, modifiers);
    }
    bool triggered(const std::string& key, int modifiers = 0) const {
        return window->triggered(key, modifiers);
    }
    // Was key triggered? (Un-trigger it if it was)
    bool triggered_once(const xd::key& key, int modifiers = 0) {
        return window->triggered_once(key, modifiers);
    }
    bool triggered_once(const std::string& key, int modifiers = 0) {
        return window->triggered_once(key, modifiers);
    }
    // Run a script
    void run_script(const std::string& script);
    // Set or get the current scripting interface
    void set_current_scripting_interface(Scripting_Interface* si) {
        current_scripting_interface = si;
    }
    Scripting_Interface* get_current_scripting_interface() {
        return current_scripting_interface;
    }
    // Play some music
    xd::music::ptr load_music(const std::string& filename);
    // Play some sound effect
    xd::sound::ptr load_sound(const std::string& filename);
    // Get the music currently playing
    xd::music::ptr playing_music() { return music; }
    // Modelview projection matrix
    xd::mat4 get_mvp() const { return geometry.mvp(); }
    // Load map file and set as current map at the end of the frame
    void set_next_map(const std::string& filename, float x, float y, Direction dir);
    // Load the map right away
    void load_map(const std::string& filename);
    // Get the map
    Map* get_map() { return map.get(); }
    // Create a new map
    void new_map(xd::ivec2 map_size, xd::ivec2 tile_size);
	// Add a canvas to current map
	void add_canvas(std::shared_ptr<Canvas> canvas);
	// Remove a canvas from current map
	void remove_canvas(std::shared_ptr<Canvas> canvas);
    // Get the camera
    Camera* get_camera() { return camera.get(); }
    // Get the player
    Map_Object* get_player() { return player.get(); }
    // Get global asset manager
    xd::asset_manager& get_asset_manager();
    // Get text renderer
    xd::simple_text_renderer& get_text_renderer() { return text_renderer; }
    // Get font
    xd::font* get_font() { return font.get(); }
    // Get all NPCs
    std::vector<std::unique_ptr<NPC>>& get_npcs() { return npcs; }
    // Get NPC with given name
    NPC* get_npc(const std::string& name);
    // Get clock
    Clock* get_clock() { return clock.get(); }
    // Is time stopped
    bool stopped() const;
    // Total game time in seconds (with multiplier)
    int total_seconds() const;
    // Time elapsed since game started (in ms)
    int ticks() const;
    // Manually set ticks
    void set_ticks(int ticks) {
        editor_ticks = ticks;
    }
    // Apply a certain shader
    void set_shader(const std::string& vertex, const std::string& fragment);
    // Save game
    void save(const std::string& filename, Save_File& save_file) const;
    // Load game
    std::unique_ptr<Save_File> load(const std::string& filename);
    // Process key-mapping string
    void process_keymap();
    // Game width
    static int game_width;
    // Game height
    static int game_height;
private:
    std::unique_ptr<xd::window> window;
    struct Impl;
    friend struct Impl;
    std::unique_ptr<Impl> pimpl;
    std::unique_ptr<Clock> clock;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Map> map;
    Scripting_Interface* current_scripting_interface;
    xd::transform_geometry geometry;
    std::shared_ptr<Map_Object> player;
    xd::music::ptr music;
    xd::font::ptr font;
    xd::simple_text_renderer text_renderer;
    std::vector<std::unique_ptr<NPC>> npcs;
    int editor_ticks;
};

#endif
