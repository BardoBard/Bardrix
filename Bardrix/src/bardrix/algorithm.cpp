//
// Created by Bardio on 22/06/2024.
//

#include <bardrix/algorithm.h>

namespace bardrix {

    // bvh_data

    bvh_data::bvh_data(const std::shared_ptr<bardrix::shape>& shape) : bvh_data(shape, shape->bounding_box()) {}

    bvh_data::bvh_data(bardrix::bounding_box box) : bvh_data(nullptr, std::move(box)) {}

    bvh_data::bvh_data(const std::shared_ptr<bardrix::shape>& shape, bardrix::bounding_box box) : shape(shape),
                                                                                                  box(std::move(box)) {}

    bool operator==(const bvh_data& lhs, const bvh_data& rhs) {
        return lhs.box == rhs.box && lhs.shape == rhs.shape;
    }

    bool operator!=(const bvh_data& lhs, const bvh_data& rhs) {
        return !(lhs == rhs);
    }

    // bvh_tree

    bool bvh_tree::shape_predicate(const std::shared_ptr<bardrix::shape>& shape_lhs,
                                   const std::shared_ptr<bardrix::shape>& shape_rhs) {
        return shape_lhs && shape_rhs &&
               shape_lhs->bounding_box().center() < shape_rhs->bounding_box().center();
    }

    bool bvh_tree::bvh_predicate(const bvh_data& box_lhs, const bvh_data& box_rhs) {
        return shape_predicate(box_lhs.shape, box_rhs.shape);
    }

    bvh_tree::bvh_tree() : binary_tree<bvh_data>(bvh_predicate) {}

    void bvh_tree::construct_bvh(std::shared_ptr<bardrix::shape>* shape, std::size_t size) noexcept {
        construct_bvh(shape, shape + size);
    }

    void bvh_tree::intersect(const ray& ray, std::vector<const bardrix::shape*>& out_hits) const noexcept {
        intersect(root, ray, out_hits);
    }

    void bvh_tree::intersect(const std::unique_ptr<node>& current, const ray& ray,
                             std::vector<const bardrix::shape*>& out_hits) const noexcept {
        if (!current) return;
        if (!current->data.box.intersects(ray)) return;

        if (current->data.shape)
            out_hits.push_back(current->data.shape.get());

        intersect(current->left, ray, out_hits);
        intersect(current->right, ray, out_hits);
    }

} // namespace bardrix