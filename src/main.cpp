#include "rtsabbatical.h"

#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"
#include "PPMFormatRender.h"

color ray_grad(const ray&r)
{
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    vec3 ray_col = (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
	return ray_col;

}

#if 1
color ray_color(const ray& r, const hittable& world, int depth=50) {
	hit_record rec;
	ray nextRay = r;
	color result(1,1,1);
	auto decimatedScale = 1.0;
	while(world.hit(nextRay, 0.001, infinity, rec) && depth > 0)
	{
		//point3 target = rec.p + rec.normal + vec3::random_unit_vector();
		//nextRay = ray(rec.p, target-rec.p);
		color attenuation;
		if(rec.mat_ptr->scatter(nextRay, rec, attenuation, nextRay))
		{
			result = result*attenuation;	
		}
		else
		{
			result *= 0;
			break;
		}
		//decimatedScale *= 0.5;
		depth--;
	}
	if(depth != 0)
	{
		//result = ray_grad(nextRay) * decimatedScale;
		result = ray_grad(nextRay)*result;
	}
	return result;
}
#else
color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return ((1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0));
}
#endif

int main()
{
	// Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
	const auto NUM_SUP_SAMP = 100;
	const auto max_depth = 50;

	// Materials
	auto mat_ball = shared_ptr<lambertian>(new lambertian(color(0.7,0.1,0.3)));
	auto mat_ground = shared_ptr<lambertian>(new lambertian(color(0.8,0.8,0.0)));
    auto mat_left   = shared_ptr<metal>(new metal(color(0.8, 0.8, 0.8), 0.3));
    auto mat_right  = shared_ptr<metal>(new metal(color(0.8, 0.6, 0.2), 1.0));

	// World
	hittable_list world;
	world.add(shared_ptr<sphere>(new sphere(point3(0,0,-1), 0.5, mat_ball)));
	world.add(shared_ptr<sphere>(new sphere(point3(-1,0,-1), 0.5, mat_left)));
	world.add(shared_ptr<sphere>(new sphere(point3(1,0,-1), 0.5, mat_right)));
	world.add(shared_ptr<sphere>(new sphere(point3(0,-100.5,-1), 100, mat_ground)));

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
			for(int superSamp = 0; superSamp < NUM_SUP_SAMP; ++superSamp)
			{
				auto u = (double(i)+random_double()) / (image_width-1);
				auto v = (double(j)+random_double()) / (image_height-1);
				ray r = cam.get_ray(u, v);
				color pixel_color = ray_color(r, world, max_depth);
				ppm.sumPixel((image_height-1)-j, i, pixel_color);
			}
			ppm.avgPixel((image_height-1)-j, i, NUM_SUP_SAMP);
		}
		std::cerr << "Percent Done: " << static_cast<float>((image_height-1)-j) / static_cast<float>(image_height-1) * 100.0 << "\r";
	}
	std::cerr << "\n";
	ppm.render();

	return 0;
}
