#include "rtsabbatical.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "PPMFormatRender.h"

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

	camera cam;

	// Render interface
	PPMRenderConfig config;
	config.setImageDim(image_width, image_height);
	config.setPixelFormat(PPM_FORMAT_P3);

	PPMFormatRender ppm;
	ppm.configRender(config);

    for (int j = image_height-1; j >=0 ; j--)
	{
		for (int i = 0; i < image_width; ++i)
		{
			for(int superSamp = 0; superSamp < 100; ++superSamp)
			{
				auto u = (double(i)+random_double()) / (image_width-1);
				auto v = (double(j)+random_double()) / (image_height-1);
				//ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
				ray r = cam.get_ray(u, v);
				color pixel_color = ray_color(r, world);
				ppm.sumPixel((image_height-1)-j, i, pixel_color, 100);
			}
		}
	}
	ppm.render();

	return 0;
}
