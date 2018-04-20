#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "vertex.h"
#include "face.h"
#include "serializable_geometry.h"

#include <QDir>
#include <QString>
#include <QFileInfo>

#include <vector>
#include <set>

class Object3d : public SerializableGeometry
{
public:
    std::vector<Vertex> get_vertices() const;
    std::vector<Face> get_faces() const;

    virtual QString get_textures_palette_name() const override;
    virtual QDir get_textures_folder() const override;
    virtual std::set<QString> all_texture_names() const override;

private:
    virtual void read(std::istream& io_s) override;
    virtual void write(std::ostream& io_s) const override;

private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
    float m_scale = 1.f;
};

#endif // OBJECT_3D_H
