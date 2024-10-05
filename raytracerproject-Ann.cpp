#include <iostream>
#include <vector>
#include <assert.h>
#include <string.h>
#include <fstream>
struct Tuple //arithmetic functions for the Tuple
{
    float x, y, z, w;
    Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Tuple operator+(const Tuple &other) const //adds a Tuple to another Tuple
    {

        return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Tuple operator-(const Tuple &other) const //subtracts a Tuple to another Tuple
    {
        return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Tuple operator*(const float scalar) const //multiplies a Tuple to another Tuple
    {
        return Tuple(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Tuple operator/(const float scalar) const //Divides a Tuple to another Tuple
    {
        return Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
    }
    float magnitude() const //Find the magnitude of a Tuple
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }
    Tuple normalize() const //Finds the unit vector of a Tuple
    {
        float mag = magnitude();
        return Tuple(x / mag, y / mag, z / mag, w);
    }
    Tuple operator-() const //Changes the direction to the opposite direction of the Tuple
    {
        return Tuple(-x, -y, -z, -w);
    }
};
struct Color //Arithmetic functions of Color
{
    float red, green, blue;
    Color(float red, float green, float blue) : red(red), green(green), blue(blue) {}

    Color operator+(const Color &other) const   //adds a Color to another Color
    {

        return Color(red + other.red, green + other.green, blue + other.blue);
    }

    Color operator-(const Color &other) const //Subtracts a Color to another Color
    {

        return Color(red - other.red, green - other.green, blue - other.blue);
    }

    Color operator*(const float scalar) const //Multiplies a Color by a scaler
    {
        return Color(red * scalar, green * scalar, blue * scalar);
    }
    Color operator*(const Color &other) const //Multiplies a Color to another Color
    {
        return Color(red * other.red, green * other.green, blue * other.blue);
    }
};

struct Canvas //Build the Canvas
{
    int width, length;
    std::vector<std::vector<Color> > pixels;

    Canvas(int w, int l) : width(w), length(l), pixels(w, std::vector<Color>(l, Color(0, 0, 0))) {}

    void write_pixel(int x, int y, Color color)
    {
        pixels[x][y] = color;
    }
};

float dot(const Tuple &a, const Tuple &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Tuple cross(const Tuple &a, const Tuple &b)
{
    return Tuple(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
        0.0);
}

Tuple p(float x, float y, float z) { return Tuple(x, y, z, 1.0); }
Tuple v(float x, float y, float z) { return Tuple(x, y, z, 0.0); }
Tuple t(float x, float y, float z, float w) { return Tuple(x, y, z, w); };

void testMagnitude()
{
    Tuple v1 = v(-1, -2, -3);
    std::vector<Tuple> vectors;
    vectors.push_back(v1);

    for (size_t i = 0; i < vectors.size(); ++i)
    {
        float magnitude = vectors[i].magnitude();
        assert(abs(magnitude - sqrt(14)) < 0.001);

        Tuple unit_vector = vectors[i].normalize();
    }
}

void testDotProduct()
{
    Tuple a = v(1, 2, 3);
    Tuple b = v(2, 3, 4);
    float result = dot(a, b);
    assert(result == 20.0);
}

void testCrossProduct()
{
    Tuple a = v(1, 2, 3);
    Tuple b = v(2, 3, 4);

    Tuple result1 = cross(a, b);
    assert(result1.x == -1 && result1.y == 2 && result1.z == -1 && result1.w == 0);

    Tuple result2 = cross(b, a);
    assert(result2.x == 1 && result2.y == -2 && result2.z == 1 && result2.w == 0);
}

struct Projectile
{
    Tuple position;
    Tuple velocity;

    Projectile(Tuple pos, Tuple vel) : position(pos), velocity(vel) {}
};

struct Environment
{
    Tuple gravity;
    Tuple wind;

    Environment(Tuple grav, Tuple wnd) : gravity(grav), wind(wnd) {}
};

Projectile tick(const Environment &env, const Projectile &proj)
{
    Tuple new_position = proj.position + proj.velocity;
    Tuple new_velocity = proj.velocity + env.gravity + env.wind;
    return Projectile(new_position, new_velocity);
}

void testProjectileSimulation()
{
    Projectile p = Projectile(v(0, 1, 0), v(1, 1, 0).normalize());
    Environment e = Environment(v(0, -0.1, 0), v(-0.01, 0, 0));

    for (int i = 0; i < 10; ++i)
    {
        p = tick(e, p);
    }
}

bool close(float x, float y)
{
    return (abs(x - y) <= 0.0001);
}

int rgb(float x)
{
    if (x >= 255)
        return 255;
    if (x <= 0)
        return 0;
    return x;
}

Tuple reflect(const Tuple &v, const Tuple &n)
{
    return v - n * 2 * dot(v, n);
}

struct Light //struct for Lighting. 
{
    Tuple position;
    Color intensity;

    Light(Tuple pos, Color intense) : position(pos), intensity(intense) {}
};

struct Material //adjusts the Colors by material
{
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    Material() : color(Color(1, 1, 1)), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0) {}
};

Color lighting(const Material &material, const Light &light, const Tuple &point, const Tuple &eyev, const Tuple &normalv, bool in_shadow)
{
    Color effective_color = material.color * light.intensity; //multiplies the color to light intensity
    Color ambient = effective_color * material.ambient; //uses the effective_color to find the color of ligh near the surrounding spot

    if (in_shadow)
    {
        return ambient; //if the point lies under the shadow, the color of the point is ambient
    }

    Tuple lightv = (light.position - point).normalize();
    float light_dot_normal = dot(lightv, normalv);

    Color diffuse(0, 0, 0);
    Color specular(0, 0, 0);

    if (light_dot_normal >= 0)
    {

        diffuse = effective_color * material.diffuse * light_dot_normal;

        Tuple reflectv = reflect(-lightv, normalv);
        float reflect_dot_eye = dot(reflectv, eyev);

        if (reflect_dot_eye > 0)
        {
            float factor = pow(reflect_dot_eye, material.shininess);
            specular = light.intensity * material.specular * factor;
        }
    }

    return ambient + diffuse + specular;
}

void testColorOperation()
{
    Color c1 = Color(0.9, 0.6, 0.75);
    Color c2 = Color(0.7, 0.1, 0.25);
    Color c3 = Color(0.2, 0.3, 0.4);

    Color result_add = c1 + c2;
    assert(close(result_add.red, 1.6) && close(result_add.green, 0.7) && close(result_add.blue, 1.0));

    Color result_sub = c1 - c2;
    assert(close(result_sub.red, 0.2) && close(result_sub.green, 0.5) && close(result_sub.blue, 0.5));
}

bool hit_sphere(const Tuple &ray_origin, const Tuple &ray_direction, float radius, Tuple &hit_point)
{
    Tuple sphere_center = p(0, 0, 0); // Sphere at origin
    Tuple oc = ray_origin - sphere_center;
    float a = dot(ray_direction, ray_direction);
    float b = 2.0 * dot(oc, ray_direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return false;
    }
    else
    {
        float t = (-b - std::sqrt(discriminant)) / (2.0 * a);
        hit_point = ray_origin + ray_direction * t;
        return true;
    }
}



int main()
{
    assert(1 == 1);

    std::vector<Tuple> a1;
    std::vector<Tuple> a2;
    std::vector<Tuple> a3;
    std::vector<Tuple> a4;
    a1.push_back(p(3, 2, 1));
    a2.push_back(v(5, 6, 7));
    a3.push_back(t(0, 0, 0, 0));
    a4.push_back(t(1, -2, 3, -4));

    Tuple result_add = a1[0] + a2[0];
    assert(result_add.x == 8 && result_add.y == 8 && result_add.z == 8 && result_add.w == 1);

    Tuple result_sub = a1[0] - a2[0];
    assert(result_sub.x == -2 && result_sub.y == -4 && result_sub.z == -6 && result_sub.w == 1);

    Tuple result_neg = a3[0] - a4[0];
    assert(result_neg.x == -1 && result_neg.y == 2 && result_neg.z == -3 && result_neg.w == 4);

    Tuple result_mul = a4[0] * 3.5;
    assert(result_mul.x == 3.5 && result_mul.y == -7 && result_mul.z == 10.5 && result_mul.w == -14);

    Tuple result_div = a4[0] / 2.0;
    assert(result_div.x == 0.5 && result_div.y == -1 && result_div.z == 1.5 && result_div.w == -2);

    testMagnitude();
    testDotProduct();
    testCrossProduct();
    testProjectileSimulation();

    Light light(p(2, 5, -10), Color(0.1, 0.1, 0.1));
    Material material;
    material.ambient = 1.0;
    material.diffuse = 1.0;
    material.specular = 1.0;
    material.shininess = 600.0;
    Canvas can = Canvas(500, 500);
    std::string x = "";
    x = x + "P3" + "\n" + std::to_string(can.width) + " " + std::to_string(can.length) + "\n" + "255" + "\n";

    Tuple ray_origin = p(0, 0, -5);
    float wall_z = 10;
    float wall_size = 7.0;
    float pixel_size = wall_size / can.width;
    float half = wall_size / 2;

    Tuple sphere_center = p(0, 0, 2);
    float sphere_radius = 1.0;

    std::vector<Tuple> objects;
    objects.push_back(sphere_center);

    for (int y = 0; y < can.length; ++y)
    {
        float world_y = half - pixel_size * y;
        for (int x = 0; x < can.width; ++x)
        {
            float world_x = -half + pixel_size * x;
            Tuple position = p(world_x, world_y, wall_z);
            Tuple direction = (position - ray_origin).normalize();
            Tuple hit_point(0, 0, 0, 0);
            float t;
            if (hit_sphere(ray_origin, direction, sphere_radius, hit_point))
            {
                Tuple normalv = (hit_point - sphere_center).normalize();
                Tuple eyev = -direction;

                bool in_shadow = false;

                Color surface_color = lighting(material, light, hit_point, eyev, normalv, in_shadow);
                can.write_pixel(x, y, surface_color);
            }
            else
            {
                can.write_pixel(x, y, Color(1.0, 0.9, 1.0));
            }
        }
    }
    std::string output = "P3\n" + std::to_string(can.width) + " " + std::to_string(can.length) + "\n255\n";
    for (int y = 0; y < can.length; ++y)
    {
        for (int x = 0; x < can.width; ++x)
        {
            int r = std::round(can.pixels[x][y].red * 255); 
            int g = std::round(can.pixels[x][y].green * 255);
            int b = std::round(can.pixels[x][y].blue * 255); 
            output += std::to_string(rgb(r)) + " " + std::to_string(rgb(g)) + " " + std::to_string(rgb(b)) + " "; //adds the float as strings to the output code
        }
        output += "\n"; 
    }

    std::ofstream out("ray_final.ppm"); //sends output to the file named "ray_final.ppm"
    out << output; //output
    out.close(); 

    return 0;
}
