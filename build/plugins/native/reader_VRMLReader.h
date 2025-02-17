/**
 * This file is auto-generated by CMake, do not edit directly.
 */

#ifndef F3DVRMLReader_h
#define F3DVRMLReader_h

#include "reader.h"

#if 0
#include <.h>
#endif

#if 1
#include <vtkVRMLImporter.h>
#endif

#include <vtkVersion.h>
#include <vtksys/SystemTools.hxx>

class reader_VRMLReader : public f3d::reader
{
public:
  reader_VRMLReader() = default;

  /*
   * Get the name of this reader
   */
  const std::string getName() const override { return "VRMLReader"; }

  /*
   * Get the short description of this reader
   */
  const std::string getShortDescription() const override { return "VRML"; }

  /*
   * Get the extensions supported by this reader
   */
  const std::vector<std::string> getExtensions() const override
  {
    static const std::vector<std::string> ext = { "wrl", "vrml" };
    return ext;
  }

  /*
   * Get the mimetypes supported by this reader
   */
  virtual const std::vector<std::string> getMimeTypes() const override
  {
    static const std::vector<std::string> types = { "model/vrml" };
    return types;
  }

#if 0
  /*
   * Get the score of this reader.
   * The score is used in case several readers are able to read the file.
   * The reader having the highest score (from 0 to 100) is used to read the file.
   * Default is 50.
   */
  int getScore() const override
  {
    return ;
  }
#endif

#if 0
  /**
   * Return true if this reader can create a geometry reader
   * false otherwise
   */
  bool hasGeometryReader() override
  {
    return true;
  }

  /*
   * Create the geometry reader (VTK reader) for the given filename
   * The filename is collapsed as some VTK reader needs it to read reliably TODO add issue
   */
  vtkSmartPointer<vtkAlgorithm> createGeometryReader(const std::string& fileName) const override
  {
    vtkNew<> geomReader;
    geomReader->SetFileName(vtksys::SystemTools::CollapseFullPath(fileName).c_str());

    this->applyCustomReader(geomReader, fileName);

    return geomReader;
  }
#endif

#if 1
  /**
   * Return true if this reader can create a scene reader
   * false otherwise
   */
  bool hasSceneReader() override
  {
    return true;
  }

  /*
   * Create the scene reader (VTK importer) for the given filename
   * The filename is collapsed as some VTK reader needs it to read reliably TODO add issue
   */
  vtkSmartPointer<vtkImporter> createSceneReader(const std::string& fileName) const override
  {
    vtkNew<vtkVRMLImporter> importer;
    importer->SetFileName(vtksys::SystemTools::CollapseFullPath(fileName).c_str());

    this->applyCustomImporter(importer, fileName);

    return importer;
  }
#endif

#if 0
#include ""
#endif

};

#endif
