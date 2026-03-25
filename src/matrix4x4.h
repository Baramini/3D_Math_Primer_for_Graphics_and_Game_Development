// matrix4x4.h
struct Matrix4x4 {
    float m[4][4];

    Matrix4x4() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = (i == j) ? 1.0f : 0.0f;
    }
    Matrix4x4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
    ) {
        m[0][0]=m00; m[0][1]=m01; m[0][2]=m02; m[0][3]=m03;
        m[1][0]=m10; m[1][1]=m11; m[1][2]=m12; m[1][3]=m13;
        m[2][0]=m20; m[2][1]=m21; m[2][2]=m22; m[2][3]=m23;
        m[3][0]=m30; m[3][1]=m31; m[3][2]=m32; m[3][3]=m33;
    }

    // matrix operation
    Matrix4x4 operator+(const Matrix4x4& mat) const {
        return Matrix4x4(
            m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1], m[0][2] + mat.m[0][2], m[0][3] + mat.m[0][3],
            m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1], m[1][2] + mat.m[1][2], m[1][3] + mat.m[1][3],
            m[2][0] + mat.m[2][0], m[2][1] + mat.m[2][1], m[2][2] + mat.m[2][2], m[2][3] + mat.m[2][3],
            m[3][0] + mat.m[3][0], m[3][1] + mat.m[3][1], m[3][2] + mat.m[3][2], m[3][3] + mat.m[3][3]
        );
    }
    Matrix4x4 operator*(float scalar) const {
        return Matrix4x4(
            m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar, m[0][3] * scalar,
            m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar, m[1][3] * scalar,
            m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar, m[2][3] * scalar,
            m[3][0] * scalar, m[3][1] * scalar, m[3][2] * scalar, m[3][3] * scalar
        );
    }
    Matrix4x4 operator*(const Matrix4x4& mat) const {
        Matrix4x4 result;
        result = result.zero();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }

        return result;
    }
    Matrix4x4 transpose() const {
        return Matrix4x4(
            m[0][0], m[1][0], m[2][0], m[3][0],
            m[0][1], m[1][1], m[2][1], m[3][1],
            m[0][2], m[1][2], m[2][2], m[3][2],
            m[0][3], m[1][3], m[2][3], m[3][3]
        );
    };
    float cofactor(int r, int c) const {
        float c_array[3][3];
        int row_index = -1;
        int column_index = -1;
        for (int i = 0; i < r; i++) {
            row_index++;
            column_index = -1;
            for (int j = 0; j < c; j++) {
                column_index++;
                c_array[row_index][column_index] = m[i][j];
            }
            for (int j = c + 1; j < 4; j++) {
                column_index++;
                c_array[row_index][column_index] = m[i][j];
            }
        }
        for (int i = r + 1; i < 4; i++) {
            row_index++;
            column_index = -1;
            for (int j = 0; j < c; j++) {
                column_index++;
                c_array[row_index][column_index] = m[i][j];
            }
            for (int j = c + 1; j < 4; j++) {
                column_index++;
                c_array[row_index][column_index] = m[i][j];
            }
        }

        float result = {
            c_array[0][0] * c_array[1][1] * c_array[2][2] +
            c_array[1][0] * c_array[2][1] * c_array[0][2] +
            c_array[2][0] * c_array[0][1] * c_array[1][2] -
            c_array[0][2] * c_array[1][1] * c_array[2][0] -
            c_array[1][2] * c_array[2][1] * c_array[0][0] -
            c_array[2][2] * c_array[0][1] * c_array[1][0]
        };

        return ((r + c) % 2 == 0) ? result : -result;
    }
    float determinant() const {
        float result = 0.0f;
        for (int i = 0; i < 4; i++) {
            result += (m[0][i] * cofactor(0, i));
        }

        return result;
    }
    Matrix4x4 inverse() const;     // 역행렬 (카메라에서 핵심)

    // matrix function
    static Matrix4x4 identity();
    static Matrix4x4 zero();
    
    // Linear transformation
    static Matrix4x4 makeRotationX(float angle);
    static Matrix4x4 makeRotationY(float angle);
    static Matrix4x4 makeRotationZ(float angle);
    static Matrix4x4 makeRotation(Vector3f vec, float angle);

    static Matrix4x4 makeScale(float x, float y, float z);
    static Matrix4x4 makeScale(Vector3f vec, float k);
    static Matrix4x4 makeOrthoProj(Vector3f vec);
    static Matrix4x4 makeReflection(Vector3f vec);
    static Matrix4x4 makeSheeringXY(float s_x, float s_y);
    static Matrix4x4 makeSheeringYZ(float s_y, float s_z);
    static Matrix4x4 makeSheeringXZ(float s_x, float s_z);

    static Matrix4x4 makeTranslation(float x, float y, float z);
    
};

// matrix function
Matrix4x4 Matrix4x4::identity() {
    return Matrix4x4();
}
Matrix4x4 Matrix4x4::zero() {
    Matrix4x4 mat;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat.m[i][j] = 0.0f;
        }
    }

    return mat;
}

// rotation(affine transformation)
Matrix4x4 Matrix4x4::makeRotationX(float angle) {
    float cos_value = cosf(angle);
    float sin_value = sinf(angle);

    return Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos_value, sin_value, 0.0f,
        0.0f, -sin_value, cos_value, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4x4 Matrix4x4::makeRotationY(float angle) {
    float cos_value = cosf(angle);
    float sin_value = sinf(angle);

    return Matrix4x4(
        cos_value, 0.0f, -sin_value, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sin_value, 0.0f, cos_value, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4x4 Matrix4x4::makeRotationZ(float angle) {
    float cos_value = cosf(angle);
    float sin_value = sinf(angle);

    return Matrix4x4(
        cos_value, sin_value, 0.0f, 0.0f,
        -sin_value, cos_value, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4x4 Matrix4x4::makeRotation(Vector3f vec, float angle) {
    Vector3f n_vec = vec.normalize();
    float cos_value = cosf(angle);
    float sin_value = sinf(angle);
    float _1_sub_cos_value = 1.0f - cos_value;

    return Matrix4x4(
        n_vec.x * n_vec.x * _1_sub_cos_value + cos_value,
        n_vec.x * n_vec.y * _1_sub_cos_value + n_vec.z * sin_value,
        n_vec.x * n_vec.z * _1_sub_cos_value - n_vec.y * sin_value,
        0.0f,
        n_vec.x * n_vec.y * _1_sub_cos_value - n_vec.z * sin_value,
        n_vec.y * n_vec.y * _1_sub_cos_value + cos_value,
        n_vec.y * n_vec.z * _1_sub_cos_value + n_vec.x * sin_value,
        0.0f,
        n_vec.x * n_vec.z * _1_sub_cos_value + n_vec.y * sin_value,
        n_vec.y * n_vec.z * _1_sub_cos_value - n_vec.x * sin_value,
        n_vec.z * n_vec.z * _1_sub_cos_value + cos_value,
        0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

// scale(affine transformation)
Matrix4x4 Matrix4x4::makeScale(float x, float y, float z) {
    return Matrix4x4(
        x, 0.0f, 0.0f, 0.0f,
        0.0f, y, 0.0f, 0.0f,
        0.0f, 0.0f, z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4x4 Matrix4x4::makeScale(Vector3f vec, float k) {
    Vector3f n_vec = vec.normalize();
    float k_sub_1 = k - 1.0f;

    return Matrix4x4(
        1.0f + k_sub_1 * n_vec.x * n_vec.x,
        k_sub_1 * n_vec.x * n_vec.y,
        k_sub_1 * n_vec.x * n_vec.z,
        0.0f,
        k_sub_1 * n_vec.x * n_vec.y,
        1.0f + k_sub_1 * n_vec.y * n_vec.y,
        k_sub_1 * n_vec.y * n_vec.z,
        0.0f,
        k_sub_1 * n_vec.x * n_vec.z,
        k_sub_1 * n_vec.y * n_vec.z,
        1.0f + k_sub_1 * n_vec.z * n_vec.z,
        0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

// projection(affine transformation)
Matrix4x4 Matrix4x4::makeOrthoProj(Vector3f vec) {
    Vector3f n_vec = vec.normalize();

    return Matrix4x4(
        1.0f - n_vec.x * n_vec.x, -n_vec.x * n_vec.y, -n_vec.x * n_vec.z, 0.0f,
        -n_vec.x * n_vec.y, 1.0f - n_vec.y * n_vec.y, -n_vec.y * n_vec.z, 0.0f,
        -n_vec.x * n_vec.z, -n_vec.y * n_vec.z, 1.0f - n_vec.z * n_vec.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    ); // Equivalent to makeScale() when k = 0.0f
}

// reflection(affine transformation)
Matrix4x4 Matrix4x4::makeReflection(Vector3f vec) {
    Vector3f n_vec = vec.normalize();

    return Matrix4x4(
        1.0f - 2.0f * n_vec.x * n_vec.x, -2.0f * n_vec.x * n_vec.y, -2.0f * n_vec.x * n_vec.z, 0.0f,
        -2.0f * n_vec.x * n_vec.y, 1.0f - 2.0f * n_vec.y * n_vec.y, -2.0f * n_vec.y * n_vec.z, 0.0f,
        -2.0f * n_vec.x * n_vec.z, -2.0f * n_vec.y * n_vec.z, 1.0f - 2.0f * n_vec.z * n_vec.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    ); // Equivalent to makeScale() when k = -1.0f
}

// sheering(affine transformation)
Matrix4x4 Matrix4x4::makeSheeringXY(float s_x, float s_y) {
    return Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        s_x, s_y, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4x4 Matrix4x4::makeSheeringYZ(float s_y, float s_z) {
    return Matrix4x4(
        1.0f, s_y, s_z, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4x4 Matrix4x4::makeSheeringXZ(float s_x, float s_z) {
    return Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        s_x, 1.0f, s_z, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}