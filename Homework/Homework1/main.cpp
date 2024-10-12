#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_rotate_matrix(Eigen::Vector3f n, float angle)
{
    n = n.normalized();

    Eigen::Matrix3f I = Eigen::Matrix3f::Identity();
    Eigen::Matrix4f rotate = Eigen::Matrix4f::Identity();

    Eigen::Matrix3f N;
    N << 0, -n.z(), n.y(),
         n.z(), 0, -n.x(),
         -n.y(), n.x(), 0;

    rotate.block<3, 3>(0, 0) = (cos(angle) * I + (1 - cos(angle)) * (n * n.transpose()) + sin(angle) * N);

    return rotate;

}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model;
    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    float angle = rotation_angle / 180.0f * MY_PI;
    Eigen::Vector3f n = {1, 1, 1};

    // model << cos(angle), -sin(angle), 0, 0,
    //          sin(angle), cos(angle), 0, 0,
    //          0, 0, 1, 0,
    //          0, 0, 0, 1;
    model = get_rotate_matrix(n, angle);
    return model;

}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function
    Eigen::Matrix4f translate = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f ortho = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f perspToOrtho = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.

    eye_fov = eye_fov / 180.0 * MY_PI;
    // zNear = -zNear, zFar = -zFar;
    float t = -tan(eye_fov / 2.0) * zNear;
    float r = aspect_ratio * t;
    float l = -r;
    float b = -t;

    translate(0,3) = -(r + l) / 2.0;
    translate(1,3) = -(t + b) / 2.0;
    translate(2,3) = -(zNear + zFar) / 2.0;

    scale(0,0) = 2.0 / (r - l);
    scale(1,1) = 2.0 / (t - b);
    scale(2,2) = 2.0 / (zNear - zFar);

    ortho = scale * translate;

    perspToOrtho(0,0) = zNear;
    perspToOrtho(1,1) = zNear;
    perspToOrtho(2,2) = zNear + zFar;
    perspToOrtho(2,3) = -zNear * zFar;
    perspToOrtho(3,2) = 1;

    projection = ortho * perspToOrtho;

    return projection;
}



int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;

    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;

    }



    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;

}