#pragma once
//#include "Hitable.h"
#include <vector>
class Hitable_List : public Hitable {
	public:
		std::vector<shared_ptr<Hitable>> objects;

		Hitable_List() {};
		Hitable_List(shared_ptr<Hitable> object) { add(object); };

		void clear() { objects.clear(); };

		void add(shared_ptr<Hitable> object) {
			objects.push_back(object);
		}

		virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
			hit_record temp_rec;
			bool hit_anything = false;
			float closest_so_far = ray_t.max;
			for (const shared_ptr<Hitable>& object : objects) {
				Hitable* hitable_obj = object.get();
				if ((*hitable_obj).hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
					hit_anything = true;
					closest_so_far = temp_rec.t;
					rec = temp_rec;
				}
			}
			return hit_anything;
		}
};