#ifndef f3d_options_tools_h
#define f3d_options_tools_h

#include "options.h"
#include "types.h"

#include <algorithm>
#include <sstream>

namespace f3d
{
namespace options_tools
{

//----------------------------------------------------------------------------
/**
 * A std::string_view trim function
 */
std::string trim(std::string_view strv)
{
  constexpr std::string_view spaces = " \t\r\v\n";
  strv.remove_prefix(std::min(strv.find_first_not_of(spaces), strv.size()));
  strv.remove_suffix(std::min(strv.size() - strv.find_last_not_of(spaces) - 1, strv.size()));
  return std::string(strv);
}

//----------------------------------------------------------------------------
/** Call `std::stod` and throw `std::invalid_argument` if the whole string has not been consumed. */
double stodStrict(const std::string& str)
{
  std::size_t pos = 0;
  const double parsed = std::stod(str, &pos);
  if (pos != str.size())
  {
    throw std::invalid_argument("partial");
  }
  return parsed;
}

//----------------------------------------------------------------------------
/** Call `std::stoi` and throw `std::invalid_argument` if the whole string has not been consumed */
int stoiStrict(const std::string& str)
{
  std::size_t pos = 0;
  const int parsed = std::stoi(str, &pos);
  if (pos != str.size())
  {
    throw std::invalid_argument("partial");
  }
  return parsed;
}

//----------------------------------------------------------------------------
/**
 * Vector specific templated parse method.
 * Splits on `","` and trims chunks before parsing each element
 */
template<typename T>
struct is_vector : std::false_type
{
};
template<typename... Args>
struct is_vector<std::vector<Args...>> : std::true_type
{
};
template<typename T>
T parse(const std::string& str)
{
  static_assert(is_vector<T>::value, "non-vector types parsing must be specialized");

  // TODO implement more parsing possibilities, eg different types of tokens
  T vec;
  std::istringstream split(str);
  for (std::string each; std::getline(split, each, ',');)
  {
    vec.emplace_back(options_tools::parse<typename T::value_type>(options_tools::trim(each)));
  }
  return vec;
}

//----------------------------------------------------------------------------
/**
 * Parse provided string into a bool. Supports boolapha values as well as "yes/no" and "on/off"
 */
template<>
bool parse(const std::string& str)
{
  std::string s = str;
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
  if (s == "true" || s == "yes" || s == "on" || s == "1")
  {
    return true;
  }
  if (s == "false" || s == "no" || s == "off" || s == "0")
  {
    return false;
  }
  throw options::parsing_exception("Cannot parse " + str + " into a bool");
}

//----------------------------------------------------------------------------
/**
 * Parse provided string into an int
 * Rely on std::stoi for parsing
 * Can throw options::parsing_exception in case of failure to parse
 */
template<>
int parse(const std::string& str)
{
  try
  {
    return stoiStrict(str);
  }
  catch (std::invalid_argument const&)
  {
    throw options::parsing_exception("Cannot parse " + str + " into an int");
  }
  catch (std::out_of_range const&)
  {
    throw options::parsing_exception(
      "Cannot parse " + str + " into an int as it would go out of range");
  }
}

//----------------------------------------------------------------------------
/**
 * Parse provided string into a double
 * Rely on std::stod for parsing
 * Can throw options::parsing_exception in case of failure to parse
 */
template<>
double parse(const std::string& str)
{
  try
  {
    return stodStrict(str);
  }
  catch (std::invalid_argument const&)
  {
    throw options::parsing_exception("Cannot parse " + str + " into a double");
  }
  catch (std::out_of_range const&)
  {
    throw options::parsing_exception(
      "Cannot parse " + str + " into a double as it would go out of range");
  }
}

//----------------------------------------------------------------------------
/**
 * Parse provided string into a ratio_t.
 * Supported formats: number (same as `<double>` version), percentage, fraction
 * Can throw options::parsing_exception in case of failure to parse
 */
template<>
ratio_t parse(const std::string& str)
{
  try
  {
    if (!str.empty() && str.at(str.size() - 1) == '%')
    {
      return stodStrict(str.substr(0, str.size() - 1)) / 100;
    }

    const std::size_t sep = str.find_first_of(":/");
    if (sep != std::string::npos)
    {
      return stodStrict(str.substr(0, sep)) / stodStrict(str.substr(sep + 1));
    }

    return stodStrict(str);
  }
  catch (std::invalid_argument const&)
  {
    throw options::parsing_exception("Cannot parse " + str + " into a ratio_t");
  }
  catch (std::out_of_range const&)
  {
    throw options::parsing_exception(
      "Cannot parse " + str + " into a ratio_t as it would go out of range");
  }
}

//----------------------------------------------------------------------------
/**
 * Return provided string stripped of leading and trailing spaces.
 */
template<>
std::string parse(const std::string& str)
{
  return options_tools::trim(str);
}

// TODO Improve string generation
//----------------------------------------------------------------------------
/**
 * Format provided var into a string from provided boolean
 * using boolalpha formatting, eg: "true" or "false"
 */
std::string format(bool var)
{
  std::stringstream stream;
  stream << std::boolalpha << var;
  return stream.str();
}

//----------------------------------------------------------------------------
/**
 * Format provided var into a string from provided int
 */
std::string format(int var)
{
  return std::to_string(var);
}

//----------------------------------------------------------------------------
/**
 * Format provided var into a string from provided double
 * using ostringstream with std::noshowpoint
 */
std::string format(double var)
{
  std::ostringstream stream;
  stream << std::noshowpoint << var;
  return stream.str();
}

//----------------------------------------------------------------------------
/**
 * Format provided var into a string from provided ratio_t
 * rely on format(double&)
 */
std::string format(ratio_t var)
{
  // TODO generate a proper ratio string
  return options_tools::format(static_cast<double>(var));
}

//----------------------------------------------------------------------------
/**
 * Generate (returns) a string from provided string
 */
std::string format(const std::string& var)
{
  return var;
}

//----------------------------------------------------------------------------
/**
 * Format provided var into a string from provided double vector
 * rely on format(double&) and add `, ` between the double values
 */
template<typename T>
std::string format(const std::vector<T>& var)
{
  std::ostringstream stream;
  unsigned int i = 0;
  for (const T& elem : var)
  {
    stream << ((i > 0) ? "," : "") << options_tools::format(elem);
    i++;
  }
  return stream.str();
}

//----------------------------------------------------------------------------
/**
 * Generated method, see `options::set`
 */
void set(options& opt, std::string_view name, const option_variant_t& value)
{
  try
  {
    // clang-format off
    if (name == "interactor.invert_zoom") opt.interactor.invert_zoom = std::get<bool>(value);
    else if (name == "interactor.trackball") opt.interactor.trackball = std::get<bool>(value);
    else if (name == "model.color.opacity") opt.model.color.opacity = std::get<double>(value);
    else if (name == "model.color.rgb") opt.model.color.rgb = std::get<std::vector<double>>(value);
    else if (name == "model.color.texture") opt.model.color.texture = std::get<std::string>(value);
    else if (name == "model.emissive.factor") opt.model.emissive.factor = std::get<std::vector<double>>(value);
    else if (name == "model.emissive.texture") opt.model.emissive.texture = std::get<std::string>(value);
    else if (name == "model.matcap.texture") opt.model.matcap.texture = std::get<std::string>(value);
    else if (name == "model.material.metallic") opt.model.material.metallic = std::get<double>(value);
    else if (name == "model.material.roughness") opt.model.material.roughness = std::get<double>(value);
    else if (name == "model.material.texture") opt.model.material.texture = std::get<std::string>(value);
    else if (name == "model.normal.scale") opt.model.normal.scale = std::get<double>(value);
    else if (name == "model.normal.texture") opt.model.normal.texture = std::get<std::string>(value);
    else if (name == "model.point_sprites.enable") opt.model.point_sprites.enable = std::get<bool>(value);
    else if (name == "model.point_sprites.size") opt.model.point_sprites.size = std::get<double>(value);
    else if (name == "model.point_sprites.type") opt.model.point_sprites.type = std::get<std::string>(value);
    else if (name == "model.scivis.array_name") opt.model.scivis.array_name = std::get<std::string>(value);
    else if (name == "model.scivis.cells") opt.model.scivis.cells = std::get<bool>(value);
    else if (name == "model.scivis.colormap") opt.model.scivis.colormap = std::get<std::vector<double>>(value);
    else if (name == "model.scivis.component") opt.model.scivis.component = std::get<int>(value);
    else if (name == "model.scivis.enable") opt.model.scivis.enable = std::get<bool>(value);
    else if (name == "model.scivis.range") opt.model.scivis.range = std::get<std::vector<double>>(value);
    else if (name == "model.volume.enable") opt.model.volume.enable = std::get<bool>(value);
    else if (name == "model.volume.inverse") opt.model.volume.inverse = std::get<bool>(value);
    else if (name == "render.armature.enable") opt.render.armature.enable = std::get<bool>(value);
    else if (name == "render.backface_type") opt.render.backface_type = std::get<std::string>(value);
    else if (name == "render.background.blur.coc") opt.render.background.blur.coc = std::get<double>(value);
    else if (name == "render.background.blur.enable") opt.render.background.blur.enable = std::get<bool>(value);
    else if (name == "render.background.color") opt.render.background.color = std::get<std::vector<double>>(value);
    else if (name == "render.background.skybox") opt.render.background.skybox = std::get<bool>(value);
    else if (name == "render.effect.ambient_occlusion") opt.render.effect.ambient_occlusion = std::get<bool>(value);
    else if (name == "render.effect.anti_aliasing") opt.render.effect.anti_aliasing = std::get<bool>(value);
    else if (name == "render.effect.final_shader") opt.render.effect.final_shader = std::get<std::string>(value);
    else if (name == "render.effect.tone_mapping") opt.render.effect.tone_mapping = std::get<bool>(value);
    else if (name == "render.effect.translucency_support") opt.render.effect.translucency_support = std::get<bool>(value);
    else if (name == "render.grid.absolute") opt.render.grid.absolute = std::get<bool>(value);
    else if (name == "render.grid.color") opt.render.grid.color = std::get<std::vector<double>>(value);
    else if (name == "render.grid.enable") opt.render.grid.enable = std::get<bool>(value);
    else if (name == "render.grid.subdivisions") opt.render.grid.subdivisions = std::get<int>(value);
    else if (name == "render.grid.unit") opt.render.grid.unit = std::get<double>(value);
    else if (name == "render.hdri.ambient") opt.render.hdri.ambient = std::get<bool>(value);
    else if (name == "render.hdri.file") opt.render.hdri.file = std::get<std::string>(value);
    else if (name == "render.light.intensity") opt.render.light.intensity = std::get<double>(value);
    else if (name == "render.line_width") opt.render.line_width = std::get<double>(value);
    else if (name == "render.point_size") opt.render.point_size = std::get<double>(value);
    else if (name == "render.raytracing.denoise") opt.render.raytracing.denoise = std::get<bool>(value);
    else if (name == "render.raytracing.enable") opt.render.raytracing.enable = std::get<bool>(value);
    else if (name == "render.raytracing.samples") opt.render.raytracing.samples = std::get<int>(value);
    else if (name == "render.show_edges") opt.render.show_edges = std::get<bool>(value);
    else if (name == "scene.animation.autoplay") opt.scene.animation.autoplay = std::get<bool>(value);
    else if (name == "scene.animation.index") opt.scene.animation.index = std::get<int>(value);
    else if (name == "scene.animation.speed_factor") opt.scene.animation.speed_factor = std::get<double>(value);
    else if (name == "scene.camera.index") opt.scene.camera.index = std::get<int>(value);
    else if (name == "scene.camera.orthographic") opt.scene.camera.orthographic = std::get<bool>(value);
    else if (name == "scene.up_direction") opt.scene.up_direction = std::get<std::string>(value);
    else if (name == "ui.animation_progress") opt.ui.animation_progress = std::get<bool>(value);
    else if (name == "ui.axis") opt.ui.axis = std::get<bool>(value);
    else if (name == "ui.cheatsheet") opt.ui.cheatsheet = std::get<bool>(value);
    else if (name == "ui.console") opt.ui.console = std::get<bool>(value);
    else if (name == "ui.dropzone") opt.ui.dropzone = std::get<bool>(value);
    else if (name == "ui.dropzone_info") opt.ui.dropzone_info = std::get<std::string>(value);
    else if (name == "ui.filename") opt.ui.filename = std::get<bool>(value);
    else if (name == "ui.filename_info") opt.ui.filename_info = std::get<std::string>(value);
    else if (name == "ui.font_file") opt.ui.font_file = std::get<std::string>(value);
    else if (name == "ui.fps") opt.ui.fps = std::get<bool>(value);
    else if (name == "ui.loader_progress") opt.ui.loader_progress = std::get<bool>(value);
    else if (name == "ui.metadata") opt.ui.metadata = std::get<bool>(value);
    else if (name == "ui.scalar_bar") opt.ui.scalar_bar = std::get<bool>(value);
    else if (name == "ui.scale") opt.ui.scale = std::get<double>(value);
    // clang-format on
    else throw options::inexistent_exception("Option " + std::string(name) + " does not exist");
  }
  catch (const std::bad_variant_access&)
  {
    throw options::incompatible_exception(
      "Trying to set " + std::string(name) + " with incompatible type");
  }
}

//----------------------------------------------------------------------------
/**
 * Generated method, see `options::get`
 */
option_variant_t get(const options& opt, std::string_view name)
{
  try
  {
    // clang-format off
    if (name == "interactor.invert_zoom") return opt.interactor.invert_zoom;
  else if (name == "interactor.trackball") return opt.interactor.trackball;
  else if (name == "model.color.opacity") return opt.model.color.opacity.value();
  else if (name == "model.color.rgb") return opt.model.color.rgb.value();
  else if (name == "model.color.texture") return opt.model.color.texture.value();
  else if (name == "model.emissive.factor") return opt.model.emissive.factor.value();
  else if (name == "model.emissive.texture") return opt.model.emissive.texture.value();
  else if (name == "model.matcap.texture") return opt.model.matcap.texture.value();
  else if (name == "model.material.metallic") return opt.model.material.metallic.value();
  else if (name == "model.material.roughness") return opt.model.material.roughness.value();
  else if (name == "model.material.texture") return opt.model.material.texture.value();
  else if (name == "model.normal.scale") return opt.model.normal.scale.value();
  else if (name == "model.normal.texture") return opt.model.normal.texture.value();
  else if (name == "model.point_sprites.enable") return opt.model.point_sprites.enable;
  else if (name == "model.point_sprites.size") return opt.model.point_sprites.size;
  else if (name == "model.point_sprites.type") return opt.model.point_sprites.type;
  else if (name == "model.scivis.array_name") return opt.model.scivis.array_name.value();
  else if (name == "model.scivis.cells") return opt.model.scivis.cells;
  else if (name == "model.scivis.colormap") return opt.model.scivis.colormap;
  else if (name == "model.scivis.component") return opt.model.scivis.component;
  else if (name == "model.scivis.enable") return opt.model.scivis.enable;
  else if (name == "model.scivis.range") return opt.model.scivis.range.value();
  else if (name == "model.volume.enable") return opt.model.volume.enable;
  else if (name == "model.volume.inverse") return opt.model.volume.inverse;
  else if (name == "render.armature.enable") return opt.render.armature.enable;
  else if (name == "render.backface_type") return opt.render.backface_type.value();
  else if (name == "render.background.blur.coc") return opt.render.background.blur.coc;
  else if (name == "render.background.blur.enable") return opt.render.background.blur.enable;
  else if (name == "render.background.color") return opt.render.background.color;
  else if (name == "render.background.skybox") return opt.render.background.skybox;
  else if (name == "render.effect.ambient_occlusion") return opt.render.effect.ambient_occlusion;
  else if (name == "render.effect.anti_aliasing") return opt.render.effect.anti_aliasing;
  else if (name == "render.effect.final_shader") return opt.render.effect.final_shader.value();
  else if (name == "render.effect.tone_mapping") return opt.render.effect.tone_mapping;
  else if (name == "render.effect.translucency_support") return opt.render.effect.translucency_support;
  else if (name == "render.grid.absolute") return opt.render.grid.absolute;
  else if (name == "render.grid.color") return opt.render.grid.color;
  else if (name == "render.grid.enable") return opt.render.grid.enable;
  else if (name == "render.grid.subdivisions") return opt.render.grid.subdivisions;
  else if (name == "render.grid.unit") return opt.render.grid.unit.value();
  else if (name == "render.hdri.ambient") return opt.render.hdri.ambient;
  else if (name == "render.hdri.file") return opt.render.hdri.file.value();
  else if (name == "render.light.intensity") return opt.render.light.intensity;
  else if (name == "render.line_width") return opt.render.line_width.value();
  else if (name == "render.point_size") return opt.render.point_size.value();
  else if (name == "render.raytracing.denoise") return opt.render.raytracing.denoise;
  else if (name == "render.raytracing.enable") return opt.render.raytracing.enable;
  else if (name == "render.raytracing.samples") return opt.render.raytracing.samples;
  else if (name == "render.show_edges") return opt.render.show_edges.value();
  else if (name == "scene.animation.autoplay") return opt.scene.animation.autoplay;
  else if (name == "scene.animation.index") return opt.scene.animation.index;
  else if (name == "scene.animation.speed_factor") return opt.scene.animation.speed_factor;
  else if (name == "scene.camera.index") return opt.scene.camera.index.value();
  else if (name == "scene.camera.orthographic") return opt.scene.camera.orthographic.value();
  else if (name == "scene.up_direction") return opt.scene.up_direction;
  else if (name == "ui.animation_progress") return opt.ui.animation_progress;
  else if (name == "ui.axis") return opt.ui.axis;
  else if (name == "ui.cheatsheet") return opt.ui.cheatsheet;
  else if (name == "ui.console") return opt.ui.console;
  else if (name == "ui.dropzone") return opt.ui.dropzone;
  else if (name == "ui.dropzone_info") return opt.ui.dropzone_info;
  else if (name == "ui.filename") return opt.ui.filename;
  else if (name == "ui.filename_info") return opt.ui.filename_info;
  else if (name == "ui.font_file") return opt.ui.font_file.value();
  else if (name == "ui.fps") return opt.ui.fps;
  else if (name == "ui.loader_progress") return opt.ui.loader_progress;
  else if (name == "ui.metadata") return opt.ui.metadata;
  else if (name == "ui.scalar_bar") return opt.ui.scalar_bar;
  else if (name == "ui.scale") return opt.ui.scale;
    // clang-format on
    else throw options::inexistent_exception("Option " + std::string(name) + " does not exist");
  }
  catch (const std::bad_optional_access&)
  {
    throw options::no_value_exception("Trying to get " + std::string(name) + " before it was set");
  }
}

//----------------------------------------------------------------------------
/**
 * Generated method, see `options::getNames`
 */
std::vector<std::string> getNames()
{
  // clang-format off
  return { "interactor.invert_zoom",
  "interactor.trackball",
  "model.color.opacity",
  "model.color.rgb",
  "model.color.texture",
  "model.emissive.factor",
  "model.emissive.texture",
  "model.matcap.texture",
  "model.material.metallic",
  "model.material.roughness",
  "model.material.texture",
  "model.normal.scale",
  "model.normal.texture",
  "model.point_sprites.enable",
  "model.point_sprites.size",
  "model.point_sprites.type",
  "model.scivis.array_name",
  "model.scivis.cells",
  "model.scivis.colormap",
  "model.scivis.component",
  "model.scivis.enable",
  "model.scivis.range",
  "model.volume.enable",
  "model.volume.inverse",
  "render.armature.enable",
  "render.backface_type",
  "render.background.blur.coc",
  "render.background.blur.enable",
  "render.background.color",
  "render.background.skybox",
  "render.effect.ambient_occlusion",
  "render.effect.anti_aliasing",
  "render.effect.final_shader",
  "render.effect.tone_mapping",
  "render.effect.translucency_support",
  "render.grid.absolute",
  "render.grid.color",
  "render.grid.enable",
  "render.grid.subdivisions",
  "render.grid.unit",
  "render.hdri.ambient",
  "render.hdri.file",
  "render.light.intensity",
  "render.line_width",
  "render.point_size",
  "render.raytracing.denoise",
  "render.raytracing.enable",
  "render.raytracing.samples",
  "render.show_edges",
  "scene.animation.autoplay",
  "scene.animation.index",
  "scene.animation.speed_factor",
  "scene.camera.index",
  "scene.camera.orthographic",
  "scene.up_direction",
  "ui.animation_progress",
  "ui.axis",
  "ui.cheatsheet",
  "ui.console",
  "ui.dropzone",
  "ui.dropzone_info",
  "ui.filename",
  "ui.filename_info",
  "ui.font_file",
  "ui.fps",
  "ui.loader_progress",
  "ui.metadata",
  "ui.scalar_bar",
  "ui.scale" };
  // clang-format on
}

//----------------------------------------------------------------------------
/**
 * Generated method, see `options::setAsString`
 */
void setAsString(options& opt, std::string_view name, const std::string& str)
{
  // clang-format off
  if (name == "interactor.invert_zoom") opt.interactor.invert_zoom = options_tools::parse<bool>(str);
  else if (name == "interactor.trackball") opt.interactor.trackball = options_tools::parse<bool>(str);
  else if (name == "model.color.opacity") opt.model.color.opacity = options_tools::parse<double>(str);
  else if (name == "model.color.rgb") opt.model.color.rgb = options_tools::parse<std::vector<double>>(str);
  else if (name == "model.color.texture") opt.model.color.texture = options_tools::parse<std::string>(str);
  else if (name == "model.emissive.factor") opt.model.emissive.factor = options_tools::parse<std::vector<double>>(str);
  else if (name == "model.emissive.texture") opt.model.emissive.texture = options_tools::parse<std::string>(str);
  else if (name == "model.matcap.texture") opt.model.matcap.texture = options_tools::parse<std::string>(str);
  else if (name == "model.material.metallic") opt.model.material.metallic = options_tools::parse<double>(str);
  else if (name == "model.material.roughness") opt.model.material.roughness = options_tools::parse<double>(str);
  else if (name == "model.material.texture") opt.model.material.texture = options_tools::parse<std::string>(str);
  else if (name == "model.normal.scale") opt.model.normal.scale = options_tools::parse<double>(str);
  else if (name == "model.normal.texture") opt.model.normal.texture = options_tools::parse<std::string>(str);
  else if (name == "model.point_sprites.enable") opt.model.point_sprites.enable = options_tools::parse<bool>(str);
  else if (name == "model.point_sprites.size") opt.model.point_sprites.size = options_tools::parse<double>(str);
  else if (name == "model.point_sprites.type") opt.model.point_sprites.type = options_tools::parse<std::string>(str);
  else if (name == "model.scivis.array_name") opt.model.scivis.array_name = options_tools::parse<std::string>(str);
  else if (name == "model.scivis.cells") opt.model.scivis.cells = options_tools::parse<bool>(str);
  else if (name == "model.scivis.colormap") opt.model.scivis.colormap = options_tools::parse<std::vector<double>>(str);
  else if (name == "model.scivis.component") opt.model.scivis.component = options_tools::parse<int>(str);
  else if (name == "model.scivis.enable") opt.model.scivis.enable = options_tools::parse<bool>(str);
  else if (name == "model.scivis.range") opt.model.scivis.range = options_tools::parse<std::vector<double>>(str);
  else if (name == "model.volume.enable") opt.model.volume.enable = options_tools::parse<bool>(str);
  else if (name == "model.volume.inverse") opt.model.volume.inverse = options_tools::parse<bool>(str);
  else if (name == "render.armature.enable") opt.render.armature.enable = options_tools::parse<bool>(str);
  else if (name == "render.backface_type") opt.render.backface_type = options_tools::parse<std::string>(str);
  else if (name == "render.background.blur.coc") opt.render.background.blur.coc = options_tools::parse<double>(str);
  else if (name == "render.background.blur.enable") opt.render.background.blur.enable = options_tools::parse<bool>(str);
  else if (name == "render.background.color") opt.render.background.color = options_tools::parse<std::vector<double>>(str);
  else if (name == "render.background.skybox") opt.render.background.skybox = options_tools::parse<bool>(str);
  else if (name == "render.effect.ambient_occlusion") opt.render.effect.ambient_occlusion = options_tools::parse<bool>(str);
  else if (name == "render.effect.anti_aliasing") opt.render.effect.anti_aliasing = options_tools::parse<bool>(str);
  else if (name == "render.effect.final_shader") opt.render.effect.final_shader = options_tools::parse<std::string>(str);
  else if (name == "render.effect.tone_mapping") opt.render.effect.tone_mapping = options_tools::parse<bool>(str);
  else if (name == "render.effect.translucency_support") opt.render.effect.translucency_support = options_tools::parse<bool>(str);
  else if (name == "render.grid.absolute") opt.render.grid.absolute = options_tools::parse<bool>(str);
  else if (name == "render.grid.color") opt.render.grid.color = options_tools::parse<std::vector<double>>(str);
  else if (name == "render.grid.enable") opt.render.grid.enable = options_tools::parse<bool>(str);
  else if (name == "render.grid.subdivisions") opt.render.grid.subdivisions = options_tools::parse<int>(str);
  else if (name == "render.grid.unit") opt.render.grid.unit = options_tools::parse<double>(str);
  else if (name == "render.hdri.ambient") opt.render.hdri.ambient = options_tools::parse<bool>(str);
  else if (name == "render.hdri.file") opt.render.hdri.file = options_tools::parse<std::string>(str);
  else if (name == "render.light.intensity") opt.render.light.intensity = options_tools::parse<double>(str);
  else if (name == "render.line_width") opt.render.line_width = options_tools::parse<double>(str);
  else if (name == "render.point_size") opt.render.point_size = options_tools::parse<double>(str);
  else if (name == "render.raytracing.denoise") opt.render.raytracing.denoise = options_tools::parse<bool>(str);
  else if (name == "render.raytracing.enable") opt.render.raytracing.enable = options_tools::parse<bool>(str);
  else if (name == "render.raytracing.samples") opt.render.raytracing.samples = options_tools::parse<int>(str);
  else if (name == "render.show_edges") opt.render.show_edges = options_tools::parse<bool>(str);
  else if (name == "scene.animation.autoplay") opt.scene.animation.autoplay = options_tools::parse<bool>(str);
  else if (name == "scene.animation.index") opt.scene.animation.index = options_tools::parse<int>(str);
  else if (name == "scene.animation.speed_factor") opt.scene.animation.speed_factor = options_tools::parse<f3d::ratio_t>(str);
  else if (name == "scene.camera.index") opt.scene.camera.index = options_tools::parse<int>(str);
  else if (name == "scene.camera.orthographic") opt.scene.camera.orthographic = options_tools::parse<bool>(str);
  else if (name == "scene.up_direction") opt.scene.up_direction = options_tools::parse<std::string>(str);
  else if (name == "ui.animation_progress") opt.ui.animation_progress = options_tools::parse<bool>(str);
  else if (name == "ui.axis") opt.ui.axis = options_tools::parse<bool>(str);
  else if (name == "ui.cheatsheet") opt.ui.cheatsheet = options_tools::parse<bool>(str);
  else if (name == "ui.console") opt.ui.console = options_tools::parse<bool>(str);
  else if (name == "ui.dropzone") opt.ui.dropzone = options_tools::parse<bool>(str);
  else if (name == "ui.dropzone_info") opt.ui.dropzone_info = options_tools::parse<std::string>(str);
  else if (name == "ui.filename") opt.ui.filename = options_tools::parse<bool>(str);
  else if (name == "ui.filename_info") opt.ui.filename_info = options_tools::parse<std::string>(str);
  else if (name == "ui.font_file") opt.ui.font_file = options_tools::parse<std::string>(str);
  else if (name == "ui.fps") opt.ui.fps = options_tools::parse<bool>(str);
  else if (name == "ui.loader_progress") opt.ui.loader_progress = options_tools::parse<bool>(str);
  else if (name == "ui.metadata") opt.ui.metadata = options_tools::parse<bool>(str);
  else if (name == "ui.scalar_bar") opt.ui.scalar_bar = options_tools::parse<bool>(str);
  else if (name == "ui.scale") opt.ui.scale = options_tools::parse<f3d::ratio_t>(str);
  // clang-format on
  else throw options::inexistent_exception("Option " + std::string(name) + " does not exist");
}
//----------------------------------------------------------------------------
/**
 * Generated method, see `options::getAsString`
 */
std::string getAsString(const options& opt, std::string_view name)
{
  try
  {
    // clang-format off
    if (name == "interactor.invert_zoom") return options_tools::format(opt.interactor.invert_zoom);
  else if (name == "interactor.trackball") return options_tools::format(opt.interactor.trackball);
  else if (name == "model.color.opacity") return options_tools::format(opt.model.color.opacity.value());
  else if (name == "model.color.rgb") return options_tools::format(opt.model.color.rgb.value());
  else if (name == "model.color.texture") return options_tools::format(opt.model.color.texture.value());
  else if (name == "model.emissive.factor") return options_tools::format(opt.model.emissive.factor.value());
  else if (name == "model.emissive.texture") return options_tools::format(opt.model.emissive.texture.value());
  else if (name == "model.matcap.texture") return options_tools::format(opt.model.matcap.texture.value());
  else if (name == "model.material.metallic") return options_tools::format(opt.model.material.metallic.value());
  else if (name == "model.material.roughness") return options_tools::format(opt.model.material.roughness.value());
  else if (name == "model.material.texture") return options_tools::format(opt.model.material.texture.value());
  else if (name == "model.normal.scale") return options_tools::format(opt.model.normal.scale.value());
  else if (name == "model.normal.texture") return options_tools::format(opt.model.normal.texture.value());
  else if (name == "model.point_sprites.enable") return options_tools::format(opt.model.point_sprites.enable);
  else if (name == "model.point_sprites.size") return options_tools::format(opt.model.point_sprites.size);
  else if (name == "model.point_sprites.type") return options_tools::format(opt.model.point_sprites.type);
  else if (name == "model.scivis.array_name") return options_tools::format(opt.model.scivis.array_name.value());
  else if (name == "model.scivis.cells") return options_tools::format(opt.model.scivis.cells);
  else if (name == "model.scivis.colormap") return options_tools::format(opt.model.scivis.colormap);
  else if (name == "model.scivis.component") return options_tools::format(opt.model.scivis.component);
  else if (name == "model.scivis.enable") return options_tools::format(opt.model.scivis.enable);
  else if (name == "model.scivis.range") return options_tools::format(opt.model.scivis.range.value());
  else if (name == "model.volume.enable") return options_tools::format(opt.model.volume.enable);
  else if (name == "model.volume.inverse") return options_tools::format(opt.model.volume.inverse);
  else if (name == "render.armature.enable") return options_tools::format(opt.render.armature.enable);
  else if (name == "render.backface_type") return options_tools::format(opt.render.backface_type.value());
  else if (name == "render.background.blur.coc") return options_tools::format(opt.render.background.blur.coc);
  else if (name == "render.background.blur.enable") return options_tools::format(opt.render.background.blur.enable);
  else if (name == "render.background.color") return options_tools::format(opt.render.background.color);
  else if (name == "render.background.skybox") return options_tools::format(opt.render.background.skybox);
  else if (name == "render.effect.ambient_occlusion") return options_tools::format(opt.render.effect.ambient_occlusion);
  else if (name == "render.effect.anti_aliasing") return options_tools::format(opt.render.effect.anti_aliasing);
  else if (name == "render.effect.final_shader") return options_tools::format(opt.render.effect.final_shader.value());
  else if (name == "render.effect.tone_mapping") return options_tools::format(opt.render.effect.tone_mapping);
  else if (name == "render.effect.translucency_support") return options_tools::format(opt.render.effect.translucency_support);
  else if (name == "render.grid.absolute") return options_tools::format(opt.render.grid.absolute);
  else if (name == "render.grid.color") return options_tools::format(opt.render.grid.color);
  else if (name == "render.grid.enable") return options_tools::format(opt.render.grid.enable);
  else if (name == "render.grid.subdivisions") return options_tools::format(opt.render.grid.subdivisions);
  else if (name == "render.grid.unit") return options_tools::format(opt.render.grid.unit.value());
  else if (name == "render.hdri.ambient") return options_tools::format(opt.render.hdri.ambient);
  else if (name == "render.hdri.file") return options_tools::format(opt.render.hdri.file.value());
  else if (name == "render.light.intensity") return options_tools::format(opt.render.light.intensity);
  else if (name == "render.line_width") return options_tools::format(opt.render.line_width.value());
  else if (name == "render.point_size") return options_tools::format(opt.render.point_size.value());
  else if (name == "render.raytracing.denoise") return options_tools::format(opt.render.raytracing.denoise);
  else if (name == "render.raytracing.enable") return options_tools::format(opt.render.raytracing.enable);
  else if (name == "render.raytracing.samples") return options_tools::format(opt.render.raytracing.samples);
  else if (name == "render.show_edges") return options_tools::format(opt.render.show_edges.value());
  else if (name == "scene.animation.autoplay") return options_tools::format(opt.scene.animation.autoplay);
  else if (name == "scene.animation.index") return options_tools::format(opt.scene.animation.index);
  else if (name == "scene.animation.speed_factor") return options_tools::format(opt.scene.animation.speed_factor);
  else if (name == "scene.camera.index") return options_tools::format(opt.scene.camera.index.value());
  else if (name == "scene.camera.orthographic") return options_tools::format(opt.scene.camera.orthographic.value());
  else if (name == "scene.up_direction") return options_tools::format(opt.scene.up_direction);
  else if (name == "ui.animation_progress") return options_tools::format(opt.ui.animation_progress);
  else if (name == "ui.axis") return options_tools::format(opt.ui.axis);
  else if (name == "ui.cheatsheet") return options_tools::format(opt.ui.cheatsheet);
  else if (name == "ui.console") return options_tools::format(opt.ui.console);
  else if (name == "ui.dropzone") return options_tools::format(opt.ui.dropzone);
  else if (name == "ui.dropzone_info") return options_tools::format(opt.ui.dropzone_info);
  else if (name == "ui.filename") return options_tools::format(opt.ui.filename);
  else if (name == "ui.filename_info") return options_tools::format(opt.ui.filename_info);
  else if (name == "ui.font_file") return options_tools::format(opt.ui.font_file.value());
  else if (name == "ui.fps") return options_tools::format(opt.ui.fps);
  else if (name == "ui.loader_progress") return options_tools::format(opt.ui.loader_progress);
  else if (name == "ui.metadata") return options_tools::format(opt.ui.metadata);
  else if (name == "ui.scalar_bar") return options_tools::format(opt.ui.scalar_bar);
  else if (name == "ui.scale") return options_tools::format(opt.ui.scale);
    // clang-format on
    else throw options::inexistent_exception("Option " + std::string(name) + " does not exist");
  }
  catch (const std::bad_optional_access&)
  {
    throw options::no_value_exception("Trying to get " + std::string(name) + " before it was set");
  }
}

//----------------------------------------------------------------------------
/**
 * Generated method, see `options::isOptional`
 */
bool isOptional(std::string_view name)
{
  // clang-format off
  if (name == "interactor.invert_zoom") return false;
  else if (name == "interactor.trackball") return false;
  else if (name == "model.color.opacity") return true;
  else if (name == "model.color.rgb") return true;
  else if (name == "model.color.texture") return true;
  else if (name == "model.emissive.factor") return true;
  else if (name == "model.emissive.texture") return true;
  else if (name == "model.matcap.texture") return true;
  else if (name == "model.material.metallic") return true;
  else if (name == "model.material.roughness") return true;
  else if (name == "model.material.texture") return true;
  else if (name == "model.normal.scale") return true;
  else if (name == "model.normal.texture") return true;
  else if (name == "model.point_sprites.enable") return false;
  else if (name == "model.point_sprites.size") return false;
  else if (name == "model.point_sprites.type") return false;
  else if (name == "model.scivis.array_name") return true;
  else if (name == "model.scivis.cells") return false;
  else if (name == "model.scivis.colormap") return false;
  else if (name == "model.scivis.component") return false;
  else if (name == "model.scivis.enable") return false;
  else if (name == "model.scivis.range") return true;
  else if (name == "model.volume.enable") return false;
  else if (name == "model.volume.inverse") return false;
  else if (name == "render.armature.enable") return false;
  else if (name == "render.backface_type") return true;
  else if (name == "render.background.blur.coc") return false;
  else if (name == "render.background.blur.enable") return false;
  else if (name == "render.background.color") return false;
  else if (name == "render.background.skybox") return false;
  else if (name == "render.effect.ambient_occlusion") return false;
  else if (name == "render.effect.anti_aliasing") return false;
  else if (name == "render.effect.final_shader") return true;
  else if (name == "render.effect.tone_mapping") return false;
  else if (name == "render.effect.translucency_support") return false;
  else if (name == "render.grid.absolute") return false;
  else if (name == "render.grid.color") return false;
  else if (name == "render.grid.enable") return false;
  else if (name == "render.grid.subdivisions") return false;
  else if (name == "render.grid.unit") return true;
  else if (name == "render.hdri.ambient") return false;
  else if (name == "render.hdri.file") return true;
  else if (name == "render.light.intensity") return false;
  else if (name == "render.line_width") return true;
  else if (name == "render.point_size") return true;
  else if (name == "render.raytracing.denoise") return false;
  else if (name == "render.raytracing.enable") return false;
  else if (name == "render.raytracing.samples") return false;
  else if (name == "render.show_edges") return true;
  else if (name == "scene.animation.autoplay") return false;
  else if (name == "scene.animation.index") return false;
  else if (name == "scene.animation.speed_factor") return false;
  else if (name == "scene.camera.index") return true;
  else if (name == "scene.camera.orthographic") return true;
  else if (name == "scene.up_direction") return false;
  else if (name == "ui.animation_progress") return false;
  else if (name == "ui.axis") return false;
  else if (name == "ui.cheatsheet") return false;
  else if (name == "ui.console") return false;
  else if (name == "ui.dropzone") return false;
  else if (name == "ui.dropzone_info") return false;
  else if (name == "ui.filename") return false;
  else if (name == "ui.filename_info") return false;
  else if (name == "ui.font_file") return true;
  else if (name == "ui.fps") return false;
  else if (name == "ui.loader_progress") return false;
  else if (name == "ui.metadata") return false;
  else if (name == "ui.scalar_bar") return false;
  else if (name == "ui.scale") return false;
  // clang-format on
  else throw options::inexistent_exception("Option " + std::string(name) + " does not exist");
}

//----------------------------------------------------------------------------
/**
 * Generated method, see `options::reset`
 */
void reset(options& opt, std::string_view name)
{
  // clang-format off
  if (name == "interactor.invert_zoom") opt.interactor.invert_zoom = false;
  else if (name == "interactor.trackball") opt.interactor.trackball = false;
  else if (name == "model.color.opacity") opt.model.color.opacity.reset();
  else if (name == "model.color.rgb") opt.model.color.rgb.reset();
  else if (name == "model.color.texture") opt.model.color.texture.reset();
  else if (name == "model.emissive.factor") opt.model.emissive.factor.reset();
  else if (name == "model.emissive.texture") opt.model.emissive.texture.reset();
  else if (name == "model.matcap.texture") opt.model.matcap.texture.reset();
  else if (name == "model.material.metallic") opt.model.material.metallic.reset();
  else if (name == "model.material.roughness") opt.model.material.roughness.reset();
  else if (name == "model.material.texture") opt.model.material.texture.reset();
  else if (name == "model.normal.scale") opt.model.normal.scale.reset();
  else if (name == "model.normal.texture") opt.model.normal.texture.reset();
  else if (name == "model.point_sprites.enable") opt.model.point_sprites.enable = false;
  else if (name == "model.point_sprites.size") opt.model.point_sprites.size = 10.0;
  else if (name == "model.point_sprites.type") opt.model.point_sprites.type = "sphere";
  else if (name == "model.scivis.array_name") opt.model.scivis.array_name.reset();
  else if (name == "model.scivis.cells") opt.model.scivis.cells = false;
  else if (name == "model.scivis.colormap") opt.model.scivis.colormap = {0.0, 0.0, 0.0, 0.0, 0.4, 0.9, 0.0, 0.0, 0.8, 0.9, 0.9, 0.0, 1.0, 1.0, 1.0, 1.0};
  else if (name == "model.scivis.component") opt.model.scivis.component = -1;
  else if (name == "model.scivis.enable") opt.model.scivis.enable = false;
  else if (name == "model.scivis.range") opt.model.scivis.range.reset();
  else if (name == "model.volume.enable") opt.model.volume.enable = false;
  else if (name == "model.volume.inverse") opt.model.volume.inverse = false;
  else if (name == "render.armature.enable") opt.render.armature.enable = false;
  else if (name == "render.backface_type") opt.render.backface_type.reset();
  else if (name == "render.background.blur.coc") opt.render.background.blur.coc = 20.0;
  else if (name == "render.background.blur.enable") opt.render.background.blur.enable = false;
  else if (name == "render.background.color") opt.render.background.color = {0.2, 0.2, 0.2};
  else if (name == "render.background.skybox") opt.render.background.skybox = false;
  else if (name == "render.effect.ambient_occlusion") opt.render.effect.ambient_occlusion = false;
  else if (name == "render.effect.anti_aliasing") opt.render.effect.anti_aliasing = false;
  else if (name == "render.effect.final_shader") opt.render.effect.final_shader.reset();
  else if (name == "render.effect.tone_mapping") opt.render.effect.tone_mapping = false;
  else if (name == "render.effect.translucency_support") opt.render.effect.translucency_support = false;
  else if (name == "render.grid.absolute") opt.render.grid.absolute = false;
  else if (name == "render.grid.color") opt.render.grid.color = {0.0, 0.0, 0.0};
  else if (name == "render.grid.enable") opt.render.grid.enable = false;
  else if (name == "render.grid.subdivisions") opt.render.grid.subdivisions = 10;
  else if (name == "render.grid.unit") opt.render.grid.unit.reset();
  else if (name == "render.hdri.ambient") opt.render.hdri.ambient = false;
  else if (name == "render.hdri.file") opt.render.hdri.file.reset();
  else if (name == "render.light.intensity") opt.render.light.intensity = 1.0;
  else if (name == "render.line_width") opt.render.line_width.reset();
  else if (name == "render.point_size") opt.render.point_size.reset();
  else if (name == "render.raytracing.denoise") opt.render.raytracing.denoise = false;
  else if (name == "render.raytracing.enable") opt.render.raytracing.enable = false;
  else if (name == "render.raytracing.samples") opt.render.raytracing.samples = 5;
  else if (name == "render.show_edges") opt.render.show_edges.reset();
  else if (name == "scene.animation.autoplay") opt.scene.animation.autoplay = false;
  else if (name == "scene.animation.index") opt.scene.animation.index = 0;
  else if (name == "scene.animation.speed_factor") opt.scene.animation.speed_factor = 1.0;
  else if (name == "scene.camera.index") opt.scene.camera.index.reset();
  else if (name == "scene.camera.orthographic") opt.scene.camera.orthographic.reset();
  else if (name == "scene.up_direction") opt.scene.up_direction = "+Y";
  else if (name == "ui.animation_progress") opt.ui.animation_progress = false;
  else if (name == "ui.axis") opt.ui.axis = false;
  else if (name == "ui.cheatsheet") opt.ui.cheatsheet = false;
  else if (name == "ui.console") opt.ui.console = false;
  else if (name == "ui.dropzone") opt.ui.dropzone = false;
  else if (name == "ui.dropzone_info") opt.ui.dropzone_info = "";
  else if (name == "ui.filename") opt.ui.filename = false;
  else if (name == "ui.filename_info") opt.ui.filename_info = "";
  else if (name == "ui.font_file") opt.ui.font_file.reset();
  else if (name == "ui.fps") opt.ui.fps = false;
  else if (name == "ui.loader_progress") opt.ui.loader_progress = false;
  else if (name == "ui.metadata") opt.ui.metadata = false;
  else if (name == "ui.scalar_bar") opt.ui.scalar_bar = false;
  else if (name == "ui.scale") opt.ui.scale = 1.0;
  // clang-format on
  else throw options::inexistent_exception("Option " + std::string(name) + " does not exist");
}

} // option_tools
} // f3d
#endif // f3d_options_tools_h
