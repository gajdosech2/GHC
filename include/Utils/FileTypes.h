/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#pragma once

#include <string>
#include <vector>
#include <map>

#include <Utils/ExtSTD.h>


//! Definitions and functions for file types supported by codebase.
namespace file_types
{
  /*!
    \brief
      Enum class that specifies (geometry) file types that we recognize.

      Recognized file formats:
        .praw       - Photoneo raw scan file          Photoneo
        .cogs       - Skeletex file format            Skeletex
        .ply        - "Polygon File Format"                         "https://en.wikipedia.org/wiki/PLY_(file_format)"
        .obj        -                                 Wavefront     "https://en.wikipedia.org/wiki/Wavefront_.obj_file"
        .dae        - "Digital Asset Exchange File"   Collada       "https://fileinfo.com/extension/dae"
        .stl        - "stereolithography"                           "https://en.wikipedia.org/wiki/STL_(file_format)"
        .fbx        - "Autodesk Filmbox"              Autodesk      "https://en.wikipedia.org/wiki/FBX"
        .bvh        - "Biovision Hierarchy"                         "https://en.wikipedia.org/wiki/Biovision_Hierarchy"
  */
  enum class Type : uint8_t
  {
    praw,
    cogs,
    ply,
    obj,
    dae,
    stl,
    fbx,
    bvh,
    __count
  };



  //! A map of all file types and their extensions.
  static const std::map<Type, std::string> file_extensions =
  {
    { Type::praw, "praw" },
    { Type::cogs, "cogs" },
    { Type::ply, "ply" },
    { Type::obj, "obj" },
    { Type::dae, "dae" },
    { Type::stl, "stl" },
    { Type::fbx, "fbx" },
    { Type::bvh, "bvh" },
  };

  //! All file types defined.
  static const std::vector<Type> all_types = std_ext::Transformed(
      file_extensions,
      [](const std::pair<Type, std::string> &pair)->Type { return pair.first; });



  /*!
    \brief    Recognized file types that can have a scan and that we can import.
    \warning  Whether they do contain a scan or not is not guaranteed!
  */
  static const std::vector<Type> importable_scan_types
  {
    Type::praw,
    Type::cogs,
    Type::ply,
  };

  /*!
    \brief    Recognized file types that can have a scan and that we can export.
  */
  static const std::vector<Type> exportable_scan_types
  {
    Type::cogs,
    Type::ply
  };

  /*!
    \brief    Recognized file types that can have a point cloud and that we can import.
    \warning  Whether they do contain a point cloud or not is not guaranteed!
  */
  static const std::vector<Type> importable_point_cloud_types
  {
    Type::cogs,
    Type::obj,
    Type::fbx,
    Type::ply,
  };

  /*!
    \brief    Recognized file types that can have a point cloud and that we can export.
  */
  static const std::vector<Type> exportable_point_cloud_types
  {
    Type::cogs,
    Type::obj,
    Type::fbx,
    Type::ply,
  };

  /*!
    \brief    Recognized file types that can have a mesh and that we can import.
    \warning  Whether they do have a mesh or not is not guaranteed!
  */
  static const std::vector<Type> importable_mesh_types
  {
    Type::cogs,
    Type::dae,
    Type::obj,
    Type::fbx,
    Type::ply,
    Type::stl,
  };

  /*!
    \brief    Recognized file types that can have a mesh and that we can export.
  */
  static const std::vector<Type> exportable_mesh_types
  {
    Type::cogs,
    Type::dae,
    Type::obj,
    Type::fbx,
    Type::ply,
    Type::stl,
  };

  /*!
    \brief    Recognized assimp file types that can have a scan and/or mesh.
  */
  static const std::vector<Type> assimp_importable_types
  {
    Type::bvh,
    Type::dae,
    Type::obj,
    Type::fbx,
    Type::ply,
    Type::stl
  };

  /*!
    \brief    Cogs (internal) types.
  */
  static const std::vector<Type> cogs_types
  {
    Type::cogs,
  };


  //! Get extension from a file type. If can not deduce extension from type, returns empty string.
  [[nodiscard]]
  static inline std::string GetExt(const Type type)
  {
    if (std_ext::Contains(type, file_extensions))
    {
      return file_extensions.at(type);
    }
    return "";
  }

  //! Get extension from a file type.
  [[nodiscard]]
  static inline std::optional<file_types::Type> GetType(const std::string &filename)
  {
    static const std::unordered_map<std::string, Type> type_for_ext =
    {
      {GetExt(Type::praw), Type::praw},
      {GetExt(Type::cogs), Type::cogs},
      {GetExt(Type::ply), Type::ply},
      {GetExt(Type::obj), Type::obj},
      {GetExt(Type::dae), Type::dae},
      {GetExt(Type::stl), Type::stl},
      {GetExt(Type::fbx), Type::fbx},
      {GetExt(Type::bvh), Type::bvh}
    };
    const auto ext = std_ext::Lowercase(filename.substr(filename.find_last_of('.') + 1));
    if (std_ext::Contains(ext, type_for_ext))
    {
      return type_for_ext.at(ext);
    }
    return std::nullopt;
  }

  //! Checks if specified extension corresponds with specified type.
  [[nodiscard]]
  static inline bool IsType(const std::string &ext, file_types::Type type)
  {
    const auto etype = GetType(ext);
    return etype.has_value() && etype == type;
  }
}
