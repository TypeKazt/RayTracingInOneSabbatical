#include "rtsabbatical.h"

#include "hittable_list.h"
#include "sphere.h"
#include "PPMFormatRender.h"

#define CLAMP(X,Y) X > Y ? Y : X

color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if(world.hit(r, 0, infinity, rec))
	{
		return ((rec.normal+vec3(1,1,1))*0.5)*255.99;
	}
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    vec3 ray_col = (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
	return ray_col*vec3(255.99, 255.99, 255.99);
}

int main()
{
	// Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

	// World
	hittable_list world;
	//world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
	world.add(shared_ptr<sphere>(new sphere(point3(0,0,-1), 0.5)));
	//world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
	world.add(shared_ptr<sphere>(new sphere(point3(0,-100.5,-1), 100)));

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);



	PPMRenderConfig config;
	config.setImageDim(image_width, image_height);
	config.setPixelFormat(PPM_FORMAT_P3);

	PPMFormatRender ppm;
	ppm.configRender(config);

    for (int j = image_height-1; j >=0 ; j--)
	{
		for (int i = 0; i < image_width; ++i)
		{
			//color pixel_color((static_cast<double>(j)/image_height)*155.0, (static_cast<double>(i)/image_width)*155.0, 1);
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r, world);
			ppm.setPixel((image_height-1)-j, i, pixel_color);
		}
	}
	ppm.render();

	return 0;
}
