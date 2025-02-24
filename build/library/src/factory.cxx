#include "factory.h"

#include "log.h"
// clang-format off
extern f3d::plugin* init_plugin_static_native();
extern f3d::plugin* init_plugin_static_exodus();
// clang-format on

namespace f3d
{
//----------------------------------------------------------------------------
factory* factory::instance()
{
  static factory instance;
  return &instance;
}

//----------------------------------------------------------------------------
factory::factory()
{
  // clang-format off
  this->StaticPluginInitializers["native"] = init_plugin_static_native;
  this->StaticPluginInitializers["exodus"] = init_plugin_static_exodus;
  // clang-format on
}

//----------------------------------------------------------------------------
const std::vector<plugin*>& factory::getPlugins()
{
  return this->Plugins;
}

//----------------------------------------------------------------------------
factory::plugin_initializer_t factory::getStaticInitializer(const std::string& pluginName)
{
  auto it = this->StaticPluginInitializers.find(pluginName);
  if (it != this->StaticPluginInitializers.end())
  {
    return it->second;
  }
  return nullptr;
}

//----------------------------------------------------------------------------
reader* factory::getReader(const std::string& fileName)
{
  int bestScore = -1;
  reader* bestReader = nullptr;

  for (auto p : this->Plugins)
  {
    for (auto r : p->getReaders())
    {
      if (r->getScore() > bestScore && r->canRead(fileName))
      {
        bestScore = r->getScore();
        bestReader = r.get();
      }
    }
  }

  return bestReader;
}

//----------------------------------------------------------------------------
void factory::load(plugin* plug)
{
  if (!this->registerOnce(plug))
  {
    log::debug("A plugin named \"" + plug->getName() + "\" is already registered.");
  }
}

//----------------------------------------------------------------------------
void factory::autoload()
{
  for (auto& [str, init] : this->StaticPluginInitializers)
  {
    this->registerOnce(init());
  }
}

//----------------------------------------------------------------------------
bool factory::registerOnce(plugin* plug)
{
  if (std::find(this->Plugins.begin(), this->Plugins.end(), plug) == this->Plugins.end())
  {
    this->Plugins.push_back(plug);

    log::debug("Loading plugin \"" + plug->getName() + "\"");
    log::debug("  Version: " + plug->getVersion());
    log::debug("  Description: " + plug->getDescription());
    log::debug("  Readers:");

    for (auto read : plug->getReaders())
    {
      log::debug("    " + read->getLongDescription());
    }

    return true;
  }
  return false;
}
}
