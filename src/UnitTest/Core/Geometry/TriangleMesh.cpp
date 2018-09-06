// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "UnitTest.h"

#include "Core/Geometry/TriangleMesh.h"

using namespace std;

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, Constructor)
{
    open3d::TriangleMesh tm;

    // inherited from Geometry2D
    EXPECT_EQ(open3d::Geometry::GeometryType::TriangleMesh, tm.GetGeometryType());
    EXPECT_EQ(3, tm.Dimension());

    // public member variables
    EXPECT_EQ(0, tm.vertices_.size());
    EXPECT_EQ(0, tm.vertex_normals_.size());
    EXPECT_EQ(0, tm.vertex_colors_.size());
    EXPECT_EQ(0, tm.triangles_.size());
    EXPECT_EQ(0, tm.triangle_normals_.size());

    // public members
    EXPECT_TRUE(tm.IsEmpty());
    EXPECT_EQ(Eigen::Vector3d(0.0, 0.0, 0.0), tm.GetMinBound());
    EXPECT_EQ(Eigen::Vector3d(0.0, 0.0, 0.0), tm.GetMaxBound());
    EXPECT_FALSE(tm.HasVertices());
    EXPECT_FALSE(tm.HasVertexNormals());
    EXPECT_FALSE(tm.HasVertexColors());
    EXPECT_FALSE(tm.HasTriangles());
    EXPECT_FALSE(tm.HasTriangleNormals());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_Destructor)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_MemberData)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, Clear)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    Eigen::Vector3i imin(0, 0, 0);
    Eigen::Vector3i imax(100, 100, 100);

    open3d::TriangleMesh tm;

    tm.vertices_.resize(size);
    tm.vertex_normals_.resize(size);
    tm.vertex_colors_.resize(size);
    tm.triangles_.resize(size);
    tm.triangle_normals_.resize(size);

    UnitTest::Rand(tm.vertices_,         dmin, dmax, 0);
    UnitTest::Rand(tm.vertex_normals_,   dmin, dmax, 0);
    UnitTest::Rand(tm.vertex_colors_,    dmin, dmax, 0);
    UnitTest::Rand(tm.triangles_,        imin, imax, 0);
    UnitTest::Rand(tm.triangle_normals_, dmin, dmax, 0);

    Eigen::Vector3d minBound = tm.GetMinBound();
    Eigen::Vector3d maxBound = tm.GetMaxBound();

    EXPECT_FALSE(tm.IsEmpty());
    EXPECT_NEAR( 20.023049, minBound(0, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(  3.231460, minBound(1, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(  3.578574, minBound(2, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(997.798999, maxBound(0, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(998.924518, maxBound(1, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(999.993571, maxBound(2, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_TRUE(tm.HasVertices());
    EXPECT_TRUE(tm.HasVertexNormals());
    EXPECT_TRUE(tm.HasVertexColors());
    EXPECT_TRUE(tm.HasTriangles());
    EXPECT_TRUE(tm.HasTriangleNormals());

    tm.Clear();

    minBound = tm.GetMinBound();
    maxBound = tm.GetMaxBound();

    // public members
    EXPECT_TRUE(tm.IsEmpty());
    EXPECT_NEAR(0.0, minBound(0, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(0.0, minBound(1, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(0.0, minBound(2, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(0.0, maxBound(0, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(0.0, maxBound(1, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(0.0, maxBound(2, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_FALSE(tm.HasVertices());
    EXPECT_FALSE(tm.HasVertexNormals());
    EXPECT_FALSE(tm.HasVertexColors());
    EXPECT_FALSE(tm.HasTriangles());
    EXPECT_FALSE(tm.HasTriangleNormals());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, IsEmpty)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    open3d::TriangleMesh tm;

    EXPECT_TRUE(tm.IsEmpty());

    tm.vertices_.resize(size);

    EXPECT_FALSE(tm.IsEmpty());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, GetMinBound)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    open3d::TriangleMesh tm;

    tm.vertices_.resize(size);
    UnitTest::Rand(tm.vertices_, dmin, dmax, 0);

    Eigen::Vector3d minBound = tm.GetMinBound();

    EXPECT_NEAR( 20.023049, minBound(0, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(  3.231460, minBound(1, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(  3.578574, minBound(2, 0), UnitTest::THRESHOLD_1E_6);
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, GetMaxBound)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    open3d::TriangleMesh tm;

    tm.vertices_.resize(size);
    UnitTest::Rand(tm.vertices_, dmin, dmax, 0);

    Eigen::Vector3d maxBound = tm.GetMaxBound();

    EXPECT_NEAR(997.798999, maxBound(0, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(998.924518, maxBound(1, 0), UnitTest::THRESHOLD_1E_6);
    EXPECT_NEAR(999.993571, maxBound(2, 0), UnitTest::THRESHOLD_1E_6);
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, Transform)
{
    vector<Eigen::Vector3d> ref_vertices =
    {
        { 398.225124,1205.693071, 881.868153 },\
        { 321.838886,1085.294390, 831.611417 },\
        { 270.900608, 823.791432, 409.198658 },\
        { 339.937683,1004.432856, 615.608467 },\
        { 425.227547,1157.793590, 484.511386 },\
        { 434.350931,1342.432421, 967.169396 },\
        { 140.844202, 447.193004, 190.052250 },\
        { 293.388019, 767.506059, 320.900694 },\
        { 135.193922, 410.559494, 195.502569 },\
        { 276.542855, 807.338946, 221.948633 } \
    };

    vector<Eigen::Vector3d> ref_vertex_normals =
    {
        { 397.825124,1204.893071, 881.748153 },\
        { 321.438886,1084.494390, 831.491417 },\
        { 270.500608, 822.991432, 409.078658 },\
        { 339.537683,1003.632856, 615.488467 },\
        { 424.827547,1156.993590, 484.391386 },\
        { 433.950931,1341.632421, 967.049396 },\
        { 140.444202, 446.393004, 189.932250 },\
        { 292.988019, 766.706059, 320.780694 },\
        { 134.793922, 409.759494, 195.382569 },\
        { 276.142855, 806.538946, 221.828633 } \
    };

    vector<Eigen::Vector3d> ref_triangle_normals =
    {
        { 397.825124,1204.893071, 881.748153 },\
        { 321.438886,1084.494390, 831.491417 },\
        { 270.500608, 822.991432, 409.078658 },\
        { 339.537683,1003.632856, 615.488467 },\
        { 424.827547,1156.993590, 484.391386 },\
        { 433.950931,1341.632421, 967.049396 },\
        { 140.444202, 446.393004, 189.932250 },\
        { 292.988019, 766.706059, 320.780694 },\
        { 134.793922, 409.759494, 195.382569 },\
        { 276.142855, 806.538946, 221.828633 } \
    };

    int size = 10;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    open3d::TriangleMesh tm;

    tm.vertices_.resize(size);
    tm.vertex_normals_.resize(size);
    tm.triangle_normals_.resize(size);

    UnitTest::Rand(tm.vertices_,         dmin, dmax, 0);
    UnitTest::Rand(tm.vertex_normals_,   dmin, dmax, 0);
    UnitTest::Rand(tm.triangle_normals_, dmin, dmax, 0);

    Eigen::Matrix4d transformation;
    transformation << 0.10, 0.20, 0.30, 0.40,
                      0.50, 0.60, 0.70, 0.80,
                      0.90, 0.10, 0.11, 0.12,
                      0.13, 0.14, 0.15, 0.16;

    tm.Transform(transformation);

    for (size_t i = 0; i < tm.vertices_.size(); i++)
    {
        EXPECT_NEAR(ref_vertices[i](0, 0), tm.vertices_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertices[i](1, 0), tm.vertices_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertices[i](2, 0), tm.vertices_[i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(ref_vertex_normals[i](0, 0), tm.vertex_normals_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertex_normals[i](1, 0), tm.vertex_normals_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertex_normals[i](2, 0), tm.vertex_normals_[i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(ref_triangle_normals[i](0, 0), tm.triangle_normals_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_triangle_normals[i](1, 0), tm.triangle_normals_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_triangle_normals[i](2, 0), tm.triangle_normals_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, OperatorAppend)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    Eigen::Vector3i imin(0, 0, 0);
    Eigen::Vector3i imax(100, 100, 100);

    open3d::TriangleMesh tm0;
    open3d::TriangleMesh tm1;

    tm0.vertices_.resize(size);
    tm0.vertex_normals_.resize(size);
    tm0.vertex_colors_.resize(size);
    tm0.triangles_.resize(size);
    tm0.triangle_normals_.resize(size);

    tm1.vertices_.resize(size);
    tm1.vertex_normals_.resize(size);
    tm1.vertex_colors_.resize(size);
    tm1.triangles_.resize(size);
    tm1.triangle_normals_.resize(size);

    UnitTest::Rand(tm0.vertices_,         dmin, dmax, 0);
    UnitTest::Rand(tm0.vertex_normals_,   dmin, dmax, 0);
    UnitTest::Rand(tm0.vertex_colors_,    dmin, dmax, 0);
    UnitTest::Rand(tm0.triangles_,        imin, imax, 0);
    UnitTest::Rand(tm0.triangle_normals_, dmin, dmax, 0);

    UnitTest::Rand(tm1.vertices_,         dmin, dmax, 0);
    UnitTest::Rand(tm1.vertex_normals_,   dmin, dmax, 0);
    UnitTest::Rand(tm1.vertex_colors_,    dmin, dmax, 1);
    UnitTest::Rand(tm1.triangles_,        imin, imax, 0);
    UnitTest::Rand(tm1.triangle_normals_, dmin, dmax, 0);

    open3d::TriangleMesh tm(tm0);
    tm += tm1;

    EXPECT_EQ(2 * size, tm.vertices_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.vertices_[i](0, 0), tm.vertices_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertices_[i](1, 0), tm.vertices_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertices_[i](2, 0), tm.vertices_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.vertices_[i](0, 0), tm.vertices_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertices_[i](1, 0), tm.vertices_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertices_[i](2, 0), tm.vertices_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    EXPECT_EQ(2 * size, tm.vertex_normals_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.vertex_normals_[i](0, 0), tm.vertex_normals_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertex_normals_[i](1, 0), tm.vertex_normals_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertex_normals_[i](2, 0), tm.vertex_normals_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.vertex_normals_[i](0, 0), tm.vertex_normals_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertex_normals_[i](1, 0), tm.vertex_normals_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertex_normals_[i](2, 0), tm.vertex_normals_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    EXPECT_EQ(2 * size, tm.vertex_colors_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.vertex_colors_[i](0, 0), tm.vertex_colors_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertex_colors_[i](1, 0), tm.vertex_colors_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertex_colors_[i](2, 0), tm.vertex_colors_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.vertex_colors_[i](0, 0), tm.vertex_colors_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertex_colors_[i](1, 0), tm.vertex_colors_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertex_colors_[i](2, 0), tm.vertex_colors_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    // NOTE: why is this offset required only for triangles?
    EXPECT_EQ(2 * size, tm.triangles_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.triangles_[i](0, 0) +    0, tm.triangles_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.triangles_[i](1, 0) +    0, tm.triangles_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.triangles_[i](2, 0) +    0, tm.triangles_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.triangles_[i](0, 0) + size, tm.triangles_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.triangles_[i](1, 0) + size, tm.triangles_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.triangles_[i](2, 0) + size, tm.triangles_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    EXPECT_EQ(2 * size, tm.triangle_normals_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.triangle_normals_[i](0, 0), tm.triangle_normals_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.triangle_normals_[i](1, 0), tm.triangle_normals_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.triangle_normals_[i](2, 0), tm.triangle_normals_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.triangle_normals_[i](0, 0), tm.triangle_normals_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.triangle_normals_[i](1, 0), tm.triangle_normals_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.triangle_normals_[i](2, 0), tm.triangle_normals_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, OperatorADD)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    Eigen::Vector3i imin(0, 0, 0);
    Eigen::Vector3i imax(100, 100, 100);

    open3d::TriangleMesh tm0;
    open3d::TriangleMesh tm1;

    tm0.vertices_.resize(size);
    tm0.vertex_normals_.resize(size);
    tm0.vertex_colors_.resize(size);
    tm0.triangles_.resize(size);
    tm0.triangle_normals_.resize(size);

    tm1.vertices_.resize(size);
    tm1.vertex_normals_.resize(size);
    tm1.vertex_colors_.resize(size);
    tm1.triangles_.resize(size);
    tm1.triangle_normals_.resize(size);

    UnitTest::Rand(tm0.vertices_,         dmin, dmax, 0);
    UnitTest::Rand(tm0.vertex_normals_,   dmin, dmax, 0);
    UnitTest::Rand(tm0.vertex_colors_,    dmin, dmax, 0);
    UnitTest::Rand(tm0.triangles_,        imin, imax, 0);
    UnitTest::Rand(tm0.triangle_normals_, dmin, dmax, 0);

    UnitTest::Rand(tm1.vertices_,         dmin, dmax, 0);
    UnitTest::Rand(tm1.vertex_normals_,   dmin, dmax, 0);
    UnitTest::Rand(tm1.vertex_colors_,    dmin, dmax, 1);
    UnitTest::Rand(tm1.triangles_,        imin, imax, 0);
    UnitTest::Rand(tm1.triangle_normals_, dmin, dmax, 0);

    open3d::TriangleMesh tm = tm0 + tm1;

    EXPECT_EQ(2 * size, tm.vertices_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.vertices_[i](0, 0), tm.vertices_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertices_[i](1, 0), tm.vertices_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertices_[i](2, 0), tm.vertices_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.vertices_[i](0, 0), tm.vertices_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertices_[i](1, 0), tm.vertices_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertices_[i](2, 0), tm.vertices_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    EXPECT_EQ(2 * size, tm.vertex_normals_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.vertex_normals_[i](0, 0), tm.vertex_normals_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertex_normals_[i](1, 0), tm.vertex_normals_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertex_normals_[i](2, 0), tm.vertex_normals_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.vertex_normals_[i](0, 0), tm.vertex_normals_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertex_normals_[i](1, 0), tm.vertex_normals_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertex_normals_[i](2, 0), tm.vertex_normals_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    EXPECT_EQ(2 * size, tm.vertex_colors_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.vertex_colors_[i](0, 0), tm.vertex_colors_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertex_colors_[i](1, 0), tm.vertex_colors_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.vertex_colors_[i](2, 0), tm.vertex_colors_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.vertex_colors_[i](0, 0), tm.vertex_colors_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertex_colors_[i](1, 0), tm.vertex_colors_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.vertex_colors_[i](2, 0), tm.vertex_colors_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    // NOTE: why is this offset required only for triangles?
    EXPECT_EQ(2 * size, tm.triangles_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.triangles_[i](0, 0) +    0, tm.triangles_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.triangles_[i](1, 0) +    0, tm.triangles_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.triangles_[i](2, 0) +    0, tm.triangles_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.triangles_[i](0, 0) + size, tm.triangles_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.triangles_[i](1, 0) + size, tm.triangles_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.triangles_[i](2, 0) + size, tm.triangles_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    EXPECT_EQ(2 * size, tm.triangle_normals_.size());
    for (size_t i = 0; i < size; i++)
    {
        EXPECT_NEAR(tm0.triangle_normals_[i](0, 0), tm.triangle_normals_[   0 + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.triangle_normals_[i](1, 0), tm.triangle_normals_[   0 + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm0.triangle_normals_[i](2, 0), tm.triangle_normals_[   0 + i](2, 0), UnitTest::THRESHOLD_1E_6);

        EXPECT_NEAR(tm1.triangle_normals_[i](0, 0), tm.triangle_normals_[size + i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.triangle_normals_[i](1, 0), tm.triangle_normals_[size + i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(tm1.triangle_normals_[i](2, 0), tm.triangle_normals_[size + i](2, 0), UnitTest::THRESHOLD_1E_6);
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, ComputeTriangleNormals)
{
    vector<Eigen::Vector3d> ref =
    {
        {  -0.518261,  -0.156046,   0.840866 },\
        {   0.801995,  -0.528776,  -0.277849 },\
        {   0.229810,  -0.456625,  -0.859466 },\
        {   0.402759,   0.818194,  -0.410297 },\
        {   0.194446,   0.544931,  -0.815623 },\
        {   0.897195,  -0.430061,   0.100439 },\
        {   0.477323,   0.726018,  -0.495036 },\
        {  -0.697751,  -0.632718,   0.335875 },\
        {   0.000000,   0.000000,   1.000000 },\
        {   0.410872,   0.867091,  -0.281670 },\
        {   0.759929,   0.565668,   0.320200 },\
        {  -0.208095,   0.198077,  -0.957842 },\
        {   0.966362,  -0.247813,   0.068805 },\
        {   0.000000,   0.000000,   1.000000 },\
        {  -0.678690,   0.424643,   0.599214 },\
        {  -0.335065,   0.774829,  -0.536071 },\
        {  -0.952870,   0.270706,   0.136957 },\
        {  -0.686222,  -0.689879,  -0.230579 },\
        {   0.550236,  -0.742202,   0.382590 },\
        {  -0.020742,  -0.750026,  -0.661083 },\
        {  -0.346660,  -0.848510,   0.399821 },\
        {   0.638685,   0.610204,  -0.468758 },\
        {  -0.199654,  -0.239632,   0.950113 },\
        {   0.384052,   0.108371,  -0.916930 },\
        {   0.000000,   0.000000,   1.000000 } \
    };

    int size = 25;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(10.0, 10.0, 10.0);

    Eigen::Vector3i imin(0, 0, 0);
    Eigen::Vector3i imax(size, size, size);

    open3d::TriangleMesh tm;

    tm.vertices_.resize(size);
    tm.triangles_.resize(size);
    UnitTest::Rand(tm.vertices_, dmin, dmax, 0);
    UnitTest::Rand(tm.triangles_, imin, imax, 1);

    tm.ComputeTriangleNormals();

    for (size_t i = 0; i < tm.triangle_normals_.size(); i++)
    {
        EXPECT_NEAR(ref[i](0, 0), tm.triangle_normals_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref[i](1, 0), tm.triangle_normals_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref[i](2, 0), tm.triangle_normals_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, ComputeVertexNormals)
{
    vector<Eigen::Vector3d> ref =
    {
        {   0.201613,  -0.402563,  -0.892914 },\
        {  -0.237824,  -0.943536,  -0.230606 },\
        {  -0.118358,   0.650000,  -0.750660 },\
        {  -0.781167,  -0.571225,   0.251951 },\
        {   0.153529,  -0.910134,  -0.384818 },\
        {   0.506797,   0.860174,  -0.057075 },\
        {  -0.700973,  -0.700398,  -0.134459 },\
        {   0.873483,  -0.032896,  -0.485741 },\
        {   0.740874,  -0.671292,  -0.021726 },\
        {  -0.495394,  -0.049694,   0.867246 },\
        {  -0.678690,   0.424643,   0.599214 },\
        {   0.197309,  -0.343394,  -0.918232 },\
        {   0.979850,  -0.000361,   0.199734 },\
        {  -0.024733,   0.674225,  -0.738112 },\
        {   0.000000,   0.000000,   1.000000 },\
        {   0.641971,   0.465792,  -0.609024 },\
        {  -0.587066,  -0.661663,  -0.466429 },\
        {   0.897195,  -0.430061,   0.100439 },\
        {   0.000000,   0.000000,   1.000000 },\
        {  -0.123570,  -0.483038,   0.866836 },\
        {  -0.899704,  -0.285927,   0.329815 },\
        {  -0.215749,   0.348860,   0.912003 },\
        {   0.609957,  -0.765307,   0.205567 },\
        {  -0.725022,   0.574645,  -0.379639 },\
        {   0.998651,  -0.017983,   0.048701 } \
    };

    int size = 25;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(10.0, 10.0, 10.0);

    Eigen::Vector3i imin(0, 0, 0);
    Eigen::Vector3i imax(size, size, size);

    open3d::TriangleMesh tm;

    tm.vertices_.resize(size);
    tm.triangles_.resize(size);
    UnitTest::Rand(tm.vertices_, dmin, dmax, 0);
    UnitTest::Rand(tm.triangles_, imin, imax, 1);

    tm.ComputeVertexNormals();

    for (size_t i = 0; i < tm.triangle_normals_.size(); i++)
    {
        EXPECT_NEAR(ref[i](0, 0), tm.vertex_normals_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref[i](1, 0), tm.vertex_normals_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref[i](2, 0), tm.vertex_normals_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, Purge)
{
    vector<Eigen::Vector3d> ref_vertices =
    {
        { 840.187717, 394.382927, 783.099224 },\
        { 798.440033, 911.647358, 197.551369 },\
        { 335.222756, 768.229595, 277.774711 },\
        { 553.969956, 477.397052, 628.870925 },\
        { 364.784473, 513.400910, 952.229725 },\
        { 916.195068, 635.711728, 717.296929 },\
        { 141.602555, 606.968876,  16.300572 },\
        { 242.886771, 137.231577, 804.176754 },\
        { 156.679089, 400.944394, 129.790447 },\
        { 108.808802, 998.924518, 218.256905 },\
        { 512.932394, 839.112235, 612.639833 },\
        { 296.031618, 637.552268, 524.287190 },\
        { 493.582987, 972.775024, 292.516784 },\
        { 771.357698, 526.744979, 769.913836 },\
        { 352.458347, 807.724520, 919.026474 },\
        {  69.755276, 949.327075, 525.995350 },\
        {  86.055848, 192.213846, 663.226927 },\
        {  20.023049, 457.701737,  63.095838 },\
        { 238.279954, 970.634132, 902.208073 },\
        { 850.919787, 266.665749, 539.760341 },\
        { 375.206976, 760.248736, 512.535364 },\
        { 667.723761, 531.606434,  39.280343 },\
        { 437.637597, 931.835056, 930.809795 } \
    };

    vector<Eigen::Vector3d> ref_vertex_normals =
    {
        { 840.187717, 394.382927, 783.099224 },\
        { 798.440033, 911.647358, 197.551369 },\
        { 335.222756, 768.229595, 277.774711 },\
        { 553.969956, 477.397052, 628.870925 },\
        { 364.784473, 513.400910, 952.229725 },\
        { 916.195068, 635.711728, 717.296929 },\
        { 141.602555, 606.968876,  16.300572 },\
        { 242.886771, 137.231577, 804.176754 },\
        { 156.679089, 400.944394, 129.790447 },\
        { 108.808802, 998.924518, 218.256905 },\
        { 512.932394, 839.112235, 612.639833 },\
        { 296.031618, 637.552268, 524.287190 },\
        { 493.582987, 972.775024, 292.516784 },\
        { 771.357698, 526.744979, 769.913836 },\
        { 352.458347, 807.724520, 919.026474 },\
        {  69.755276, 949.327075, 525.995350 },\
        {  86.055848, 192.213846, 663.226927 },\
        {  20.023049, 457.701737,  63.095838 },\
        { 238.279954, 970.634132, 902.208073 },\
        { 850.919787, 266.665749, 539.760341 },\
        { 375.206976, 760.248736, 512.535364 },\
        { 667.723761, 531.606434,  39.280343 },\
        { 437.637597, 931.835056, 930.809795 } \
    };

    vector<Eigen::Vector3d> ref_vertex_colors =
    {
        { 840.187717, 394.382927, 783.099224 },\
        { 798.440033, 911.647358, 197.551369 },\
        { 335.222756, 768.229595, 277.774711 },\
        { 553.969956, 477.397052, 628.870925 },\
        { 364.784473, 513.400910, 952.229725 },\
        { 916.195068, 635.711728, 717.296929 },\
        { 141.602555, 606.968876,  16.300572 },\
        { 242.886771, 137.231577, 804.176754 },\
        { 156.679089, 400.944394, 129.790447 },\
        { 108.808802, 998.924518, 218.256905 },\
        { 512.932394, 839.112235, 612.639833 },\
        { 296.031618, 637.552268, 524.287190 },\
        { 493.582987, 972.775024, 292.516784 },\
        { 771.357698, 526.744979, 769.913836 },\
        { 352.458347, 807.724520, 919.026474 },\
        {  69.755276, 949.327075, 525.995350 },\
        {  86.055848, 192.213846, 663.226927 },\
        {  20.023049, 457.701737,  63.095838 },\
        { 238.279954, 970.634132, 902.208073 },\
        { 850.919787, 266.665749, 539.760341 },\
        { 375.206976, 760.248736, 512.535364 },\
        { 667.723761, 531.606434,  39.280343 },\
        { 437.637597, 931.835056, 930.809795 } \
    };

    vector<Eigen::Vector3d> ref_triangles =
    {
        {    19,     9,    17 },\
        {    17,    20,     4 },\
        {     8,    17,     6 },\
        {    13,    11,    14 },\
        {     9,    12,    21 },\
        {    20,    14,    16 },\
        {     3,    14,     0 },\
        {     6,     3,    18 },\
        {     2,    22,     5 },\
        {    12,    18,    14 },\
        {     7,    14,    13 },\
        {    12,    22,     7 },\
        {    10,    20,     7 },\
        {     8,    18,    20 },\
        {     1,    21,    13 },\
        {     2,     4,    15 },\
        {    20,     8,     1 },\
        {     0,    11,     1 },\
        {     5,    22,    20 },\
        {    19,     6,    13 },\
        {     9,    17,    12 },\
        {    15,    13,     0 } \
    };

    vector<Eigen::Vector3d> ref_triangle_normals =
    {
        { 840.187717, 394.382927, 783.099224 },\
        { 798.440033, 911.647358, 197.551369 },\
        { 335.222756, 768.229595, 277.774711 },\
        { 553.969956, 477.397052, 628.870925 },\
        { 364.784473, 513.400910, 952.229725 },\
        { 916.195068, 635.711728, 717.296929 },\
        { 141.602555, 606.968876,  16.300572 },\
        { 242.886771, 137.231577, 804.176754 },\
        { 108.808802, 998.924518, 218.256905 },\
        { 512.932394, 839.112235, 612.639833 },\
        { 296.031618, 637.552268, 524.287190 },\
        { 493.582987, 972.775024, 292.516784 },\
        { 400.228622, 891.529452, 283.314746 },\
        { 352.458347, 807.724520, 919.026474 },\
        {  69.755276, 949.327075, 525.995350 },\
        {  86.055848, 192.213846, 663.226927 },\
        { 890.232603, 348.892935,  64.171321 },\
        {  20.023049, 457.701737,  63.095838 },\
        { 238.279954, 970.634132, 902.208073 },\
        { 850.919787, 266.665749, 539.760341 },\
        { 375.206976, 760.248736, 512.535364 },\
        { 667.723761, 531.606434,  39.280343 } \
    };

    int size = 25;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    Eigen::Vector3i imin(0, 0, 0);
    Eigen::Vector3i imax(size, size, size);

    open3d::TriangleMesh tm0;
    open3d::TriangleMesh tm1;

    tm0.vertices_.resize(size);
    tm0.vertex_normals_.resize(size);
    tm0.vertex_colors_.resize(size);
    tm0.triangles_.resize(size);
    tm0.triangle_normals_.resize(size);

    tm1.vertices_.resize(size);
    tm1.vertex_normals_.resize(size);
    tm1.vertex_colors_.resize(size);
    tm1.triangles_.resize(size);
    tm1.triangle_normals_.resize(size);

    UnitTest::Rand(tm0.vertices_,         dmin, dmax, 0);
    UnitTest::Rand(tm0.vertex_normals_,   dmin, dmax, 0);
    UnitTest::Rand(tm0.vertex_colors_,    dmin, dmax, 0);
    UnitTest::Rand(tm0.triangles_,        imin, imax, 0);
    UnitTest::Rand(tm0.triangle_normals_, dmin, dmax, 0);

    UnitTest::Rand(tm1.vertices_,         dmin, dmax, 0);
    UnitTest::Rand(tm1.vertex_normals_,   dmin, dmax, 0);
    UnitTest::Rand(tm1.vertex_colors_,    dmin, dmax, 1);
    UnitTest::Rand(tm1.triangles_,        imin, imax, 0);
    UnitTest::Rand(tm1.triangle_normals_, dmin, dmax, 0);

    open3d::TriangleMesh tm = tm0 + tm1;

    tm.Purge();

    EXPECT_EQ(23, tm.vertices_.size());
    for (size_t i = 0; i < tm.vertices_.size(); i++)
    {
        EXPECT_NEAR(ref_vertices[i](0, 0), tm.vertices_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertices[i](1, 0), tm.vertices_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertices[i](2, 0), tm.vertices_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    EXPECT_EQ(23, tm.vertex_normals_.size());
    for (size_t i = 0; i < tm.vertex_normals_.size(); i++)
    {
        EXPECT_NEAR(ref_vertex_normals[i](0, 0), tm.vertex_normals_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertex_normals[i](1, 0), tm.vertex_normals_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertex_normals[i](2, 0), tm.vertex_normals_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    EXPECT_EQ(23, tm.vertex_colors_.size());
    for (size_t i = 0; i < tm.vertex_colors_.size(); i++)
    {
        EXPECT_NEAR(ref_vertex_colors[i](0, 0), tm.vertex_colors_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertex_colors[i](1, 0), tm.vertex_colors_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertex_colors[i](2, 0), tm.vertex_colors_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    // NOTE: why is this offset required only for triangles?
    EXPECT_EQ(22, tm.triangles_.size());
    for (size_t i = 0; i < tm.triangles_.size(); i++)
    {
        EXPECT_NEAR(ref_triangles[i](0, 0), tm.triangles_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_triangles[i](1, 0), tm.triangles_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_triangles[i](2, 0), tm.triangles_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    EXPECT_EQ(22, tm.triangle_normals_.size());
    for (size_t i = 0; i < tm.triangle_normals_.size(); i++)
    {
        EXPECT_NEAR(ref_triangle_normals[i](0, 0), tm.triangle_normals_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_triangle_normals[i](1, 0), tm.triangle_normals_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_triangle_normals[i](2, 0), tm.triangle_normals_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, HasVertices)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    open3d::TriangleMesh tm;

    EXPECT_FALSE(tm.HasVertices());

    tm.vertices_.resize(size);

    EXPECT_TRUE(tm.HasVertices());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, HasTriangles)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    open3d::TriangleMesh tm;

    EXPECT_FALSE(tm.HasTriangles());

    tm.vertices_.resize(size);
    tm.triangles_.resize(size);

    EXPECT_TRUE(tm.HasTriangles());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, HasVertexNormals)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    open3d::TriangleMesh tm;

    EXPECT_FALSE(tm.HasVertexNormals());

    tm.vertices_.resize(size);
    tm.vertex_normals_.resize(size);

    EXPECT_TRUE(tm.HasVertexNormals());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, HasVertexColors)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    open3d::TriangleMesh tm;

    EXPECT_FALSE(tm.HasVertexColors());

    tm.vertices_.resize(size);
    tm.vertex_colors_.resize(size);

    EXPECT_TRUE(tm.HasVertexColors());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, HasTriangleNormals)
{
    int size = 100;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(1000.0, 1000.0, 1000.0);

    open3d::TriangleMesh tm;

    EXPECT_FALSE(tm.HasTriangleNormals());

    tm.vertices_.resize(size);
    tm.triangles_.resize(size);
    tm.triangle_normals_.resize(size);

    EXPECT_TRUE(tm.HasTriangleNormals());
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, NormalizeNormals)
{
    vector<Eigen::Vector3d> ref_vertex_normals =
    {
        {   0.691871,   0.324763,   0.644860 },\
        {   0.650271,   0.742470,   0.160891 },\
        {   0.379636,   0.870011,   0.314576 },\
        {   0.574357,   0.494966,   0.652014 },\
        {   0.319521,   0.449696,   0.834074 },\
        {   0.690989,   0.479450,   0.540981 },\
        {   0.227116,   0.973517,   0.026144 },\
        {   0.285349,   0.161223,   0.944766 },\
        {   0.348477,   0.891758,   0.288673 },\
        {   0.105818,   0.971468,   0.212258 },\
        {   0.442687,   0.724197,   0.528740 },\
        {   0.337582,   0.727038,   0.597875 },\
        {   0.437042,   0.861341,   0.259008 },\
        {   0.637242,   0.435160,   0.636049 },\
        {   0.393351,   0.876209,   0.278446 },\
        {   0.276810,   0.634363,   0.721776 },\
        {   0.064140,   0.872907,   0.483653 },\
        {   0.123668,   0.276225,   0.953103 },\
        {   0.928961,   0.364071,   0.066963 },\
        {   0.043296,   0.989703,   0.136434 },\
        {   0.176971,   0.720892,   0.670072 },\
        {   0.816339,   0.255829,   0.517825 },\
        {   0.378736,   0.767399,   0.517356 },\
        {   0.781510,   0.622197,   0.045974 },\
        {   0.315325,   0.671402,   0.670663 } \
    };

    vector<Eigen::Vector3d> ref_triangle_normals =
    {
        {   0.691871,   0.324763,   0.644860 },\
        {   0.650271,   0.742470,   0.160891 },\
        {   0.379636,   0.870011,   0.314576 },\
        {   0.574357,   0.494966,   0.652014 },\
        {   0.319521,   0.449696,   0.834074 },\
        {   0.690989,   0.479450,   0.540981 },\
        {   0.227116,   0.973517,   0.026144 },\
        {   0.285349,   0.161223,   0.944766 },\
        {   0.348477,   0.891758,   0.288673 },\
        {   0.105818,   0.971468,   0.212258 },\
        {   0.442687,   0.724197,   0.528740 },\
        {   0.337582,   0.727038,   0.597875 },\
        {   0.437042,   0.861341,   0.259008 },\
        {   0.637242,   0.435160,   0.636049 },\
        {   0.393351,   0.876209,   0.278446 },\
        {   0.276810,   0.634363,   0.721776 },\
        {   0.064140,   0.872907,   0.483653 },\
        {   0.123668,   0.276225,   0.953103 },\
        {   0.928961,   0.364071,   0.066963 },\
        {   0.043296,   0.989703,   0.136434 },\
        {   0.176971,   0.720892,   0.670072 },\
        {   0.816339,   0.255829,   0.517825 },\
        {   0.378736,   0.767399,   0.517356 },\
        {   0.781510,   0.622197,   0.045974 },\
        {   0.315325,   0.671402,   0.670663 } \
    };

    int size = 25;

    Eigen::Vector3d dmin(0.0, 0.0, 0.0);
    Eigen::Vector3d dmax(10.0, 10.0, 10.0);

    open3d::TriangleMesh tm;

    tm.vertex_normals_.resize(size);
    tm.triangle_normals_.resize(size);
    UnitTest::Rand(tm.vertex_normals_, dmin, dmax, 0);
    UnitTest::Rand(tm.triangle_normals_, dmin, dmax, 1);

    tm.NormalizeNormals();

    for (size_t i = 0; i < tm.vertex_normals_.size(); i++)
    {
        EXPECT_NEAR(ref_vertex_normals[i](0, 0), tm.vertex_normals_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertex_normals[i](1, 0), tm.vertex_normals_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_vertex_normals[i](2, 0), tm.vertex_normals_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }

    for (size_t i = 0; i < tm.triangle_normals_.size(); i++)
    {
        EXPECT_NEAR(ref_triangle_normals[i](0, 0), tm.triangle_normals_[i](0, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_triangle_normals[i](1, 0), tm.triangle_normals_[i](1, 0), UnitTest::THRESHOLD_1E_6);
        EXPECT_NEAR(ref_triangle_normals[i](2, 0), tm.triangle_normals_[i](2, 0), UnitTest::THRESHOLD_1E_6);
    }
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_PaintUniformColor)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_SelectDownSample)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_CropTriangleMesh)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_CreateMeshSphere)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_CreateMeshCylinder)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_CreateMeshCone)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_CreateMeshArrow)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMesh, DISABLED_CreateMeshCoordinateFrame)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMeshFactory, DISABLED_CreateMeshSphere)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMeshFactory, DISABLED_CreateMeshCylinder)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMeshFactory, DISABLED_CreateMeshCone)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMeshFactory, DISABLED_CreateMeshArrow)
{
    UnitTest::NotImplemented();
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
TEST(TriangleMeshFactory, DISABLED_CreateMeshCoordinateFrame)
{
    UnitTest::NotImplemented();
}
