#ifndef f3d_options_h
#define f3d_options_h

#include "exception.h"
#include "export.h"
#include "types.h"

#include <array>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace f3d
{
// Declared here for simplicity
using option_variant_t = std::variant<bool, int, double, std::string, std::vector<double>>;

/**
 * @class   options
 * @brief   Class used to control the different options
 *
 * A class to control the different options of f3d.
 * See the README_libf3d.md for the full listing of options.
 * The struct below can also be consulted.
 */
class F3D_EXPORT options
{
public:
  ///@{ @name Constructors
  /**
   * Default/Copy/move constructors/operators.
   */
  options();
  ~options() = default;
  options(const options& opt) = default;
  options& operator=(const options& opt) = default;
  options(options&& other) noexcept = default;
  options& operator=(options&& other) noexcept = default;
  ///@}

  /**
   * Set an option as a variant based on its name
   * Please note that, on Windows, using an explicit std::string may be required:
   * https://stackoverflow.com/questions/60681710/prefer-stdstring-in-stdvariantbool-stdstring-for-const-char
   * Throw an options::inexistent_exception if option does not exist.
   * Throw an options::incompatible_exception if value is not compatible with option.
   */
  options& set(std::string_view name, const option_variant_t& value);

  /**
   * Get an option as a variant based on its name
   * Throw an options::inexistent_exception if option does not exist.
   * Throw an options::no_value_exception if option has not been set.
   */
  [[nodiscard]] option_variant_t get(std::string_view name) const;

  /**
   * Set an option as a string based on its name
   * Use dedicated parsing code, see the related doc
   * TODO add parsing documentation
   * Throw an options::inexistent_exception if option does not exist.
   * Throw an options::parsing_exception if parsing failed.
   */
  options& setAsString(std::string_view name, const std::string& str);

  /**
   * Get an option as a string based on its name
   * Throw an options::inexistent_exception if option does not exist.
   * Throw an options::no_value_exception if option has not been set.
   */
  [[nodiscard]] std::string getAsString(std::string_view name) const;

  /**
   * A boolean option specific method to toggle it.
   * If the option has not been set yet, set it to true.
   * Throw an options::inexistent_exception if option does not exist.
   * Throw an options::incompatible_exception if option is not boolean.
   */
  options& toggle(std::string_view name);

  /**
   * Compare an option between this and a provided other.
   * Return true if they are the same value, false otherwise.
   * Throw an options::inexistent_exception if option does not exist.
   */
  [[nodiscard]] bool isSame(const options& other, std::string_view name) const;

  /**
   * Return true if an option has a value, false otherwise
   * Always returns true for non-optional options.
   * Throw an options::inexistent_exception if option does not exist.
   */
  [[nodiscard]] bool hasValue(std::string_view name) const;

  /**
   * Copy the value of an option from this to the provided other.
   * Throw an options::inexistent_exception if option does not exist.
   */
  options& copy(const options& other, std::string_view name);

  /**
   * Get all available option names.
   */
  [[nodiscard]] static std::vector<std::string> getAllNames();

  /**
   * Get all option names that currently have values.
   */
  [[nodiscard]] std::vector<std::string> getNames() const;

  /**
   * Get the closest option name and its Levenshtein distance.
   */
  [[nodiscard]] std::pair<std::string, unsigned int> getClosestOption(
    std::string_view option) const;

  /**
   *  Returns true if the option is optional else returns false.
   *  Throws an options::inexistent_exception if option does not exist.
   */
  [[nodiscard]] bool isOptional(std::string_view option) const;

  /**
   *  Resets the option to default value.
   *  Throws an options::inexistent_exception if option does not exist.
   */
  options& reset(std::string_view name);

  /**
   *  Unset the option if it is optional else throws options::incompatible_exception.
   *  Throws an options::inexistent_exception if option does not exist.
   */
  options& removeValue(std::string_view name);

  /**
   * Templated parsing method used internally to parse strings.
   * Implemented for the different supported types,
   * see PARSING.md for more info.
   * Throw an options::parsing_exception if parsing failed.
   */
  template<typename T>
  [[nodiscard]] static T parse(const std::string& str);

  /**
   * Templated parsing method used internally to format var into strings.
   * Implemented for the different supported types,
   * see PARSING.md for more info.
   */
  template<typename T>
  [[nodiscard]] static std::string format(const T& var);

  /**
   * An exception that can be thrown by the options
   * when parsing of a string into an option value fails
   */
  struct parsing_exception : public exception
  {
    explicit parsing_exception(const std::string& what = "");
  };

  /**
   * An exception that can be thrown by the options
   * when an operation on a specific option is incompatible with
   * its internal type.
   */
  struct incompatible_exception : public exception
  {
    explicit incompatible_exception(const std::string& what = "");
  };

  /**
   * An exception that can be thrown by the options
   * when a provided option does not exist.
   */
  struct inexistent_exception : public exception
  {
    explicit inexistent_exception(const std::string& what = "");
  };

  /**
   * An exception that can be thrown by the options
   * when a provided option is accessed before being set.
   */
  struct no_value_exception : public exception
  {
    explicit no_value_exception(const std::string& what = "");
  };

  /**
   * The complete generated options struct
   */
  // clang-format off
    struct interactor {
    bool invert_zoom = false;
    bool trackball = false;
  } interactor;

  struct model {
    struct color {
      std::optional<double> opacity;
      std::optional<std::vector<double>> rgb;
      std::optional<std::string> texture;
    } color;

    struct emissive {
      std::optional<std::vector<double>> factor;
      std::optional<std::string> texture;
    } emissive;

    struct matcap {
      std::optional<std::string> texture;
    } matcap;

    struct material {
      std::optional<double> metallic;
      std::optional<double> roughness;
      std::optional<std::string> texture;
    } material;

    struct normal {
      std::optional<double> scale;
      std::optional<std::string> texture;
    } normal;

    struct point_sprites {
      bool enable = false;
      double size = 10.0;
      std::string type = "sphere";
    } point_sprites;

    struct scivis {
      std::optional<std::string> array_name;
      bool cells = false;
      std::vector<double> colormap = {0.0, 0.0, 0.0, 0.0, 0.4, 0.9, 0.0, 0.0, 0.8, 0.9, 0.9, 0.0, 1.0, 1.0, 1.0, 1.0};
      int component = -1;
      bool enable = false;
      std::optional<std::vector<double>> range;
    } scivis;

    struct volume {
      bool enable = false;
      bool inverse = false;
    } volume;

  } model;

  struct render {
    struct armature {
      bool enable = false;
    } armature;

    std::optional<std::string> backface_type;
    struct background {
      struct blur {
        double coc = 20.0;
        bool enable = false;
      } blur;

      std::vector<double> color = {0.2, 0.2, 0.2};
      bool skybox = false;
    } background;

    struct effect {
      bool ambient_occlusion = false;
      bool anti_aliasing = false;
      std::optional<std::string> final_shader;
      bool tone_mapping = false;
      bool translucency_support = false;
    } effect;

    struct grid {
      bool absolute = false;
      std::vector<double> color = {0.0, 0.0, 0.0};
      bool enable = false;
      int subdivisions = 10;
      std::optional<double> unit;
    } grid;

    struct hdri {
      bool ambient = false;
      std::optional<std::string> file;
    } hdri;

    struct light {
      double intensity = 1.0;
    } light;

    std::optional<double> line_width;
    std::optional<double> point_size;
    struct raytracing {
      bool denoise = false;
      bool enable = false;
      int samples = 5;
    } raytracing;

    std::optional<bool> show_edges;
  } render;

  struct scene {
    struct animation {
      bool autoplay = false;
      int index = 0;
      f3d::ratio_t speed_factor = 1.0;
    } animation;

    struct camera {
      std::optional<int> index;
      std::optional<bool> orthographic;
    } camera;

    std::string up_direction = "+Y";
  } scene;

  struct ui {
    bool animation_progress = false;
    bool axis = false;
    bool cheatsheet = false;
    bool console = false;
    bool dropzone = false;
    std::string dropzone_info = "";
    bool filename = false;
    std::string filename_info = "";
    std::optional<std::string> font_file;
    bool fps = false;
    bool loader_progress = false;
    bool metadata = false;
    bool scalar_bar = false;
    f3d::ratio_t scale = 1.0;
  } ui;


  // clang-format on
};
}

#endif
