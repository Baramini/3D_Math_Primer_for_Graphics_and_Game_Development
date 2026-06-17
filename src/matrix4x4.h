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

    // < const function >
    // matrix operator overloading
    Matrix4x4 operator+(const Matrix4x4& mat) const;
    Matrix4x4 operator*(float scalar) const;
    Matrix4x4 operator*(const Matrix4x4& mat) const;

    // matrix function
    float cofactor(int r, int c) const;
    float determinant() const;
    Matrix4x4 transpose() const;
    Matrix4x4 inverse() const;
    Matrix4x4 orthogonalize() const;
    void printComponents() const;

    Matrix4x4 rotate(Vector3f vec, float angle) const;
    Matrix4x4 rotateX(float angle) const;
    Matrix4x4 rotateY(float angle) const;
    Matrix4x4 rotateZ(float angle) const;
    Matrix4x4 scale(float x, float y, float z) const;
    Matrix4x4 scale(Vector3f vec, float k) const;
    Matrix4x4 reflect(Vector3f vec) const;
    Matrix4x4 sheerXY(float s_x, float s_y) const;
    Matrix4x4 sheerYZ(float s_y, float s_z) const;
    Matrix4x4 sheerXZ(float s_x, float s_z) const;
    Matrix4x4 translate(float x, float y, float z) const;

    Matrix4x4 orth_proj(Vector3f vec) const;
    Matrix4x4 persp_proj(float d) const;

    // < static function >
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
    static Matrix4x4 makePerspProjZ(float d);
    static Matrix4x4 makeReflection(Vector3f vec);

    static Matrix4x4 makeSheeringXY(float s_x, float s_y);
    static Matrix4x4 makeSheeringYZ(float s_y, float s_z);
    static Matrix4x4 makeSheeringXZ(float s_x, float s_z);

    static Matrix4x4 makeTranslation(float x, float y, float z);
    
};

// matrix operation
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat) const {
    return Matrix4x4(
        m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1], m[0][2] + mat.m[0][2], m[0][3] + mat.m[0][3],
        m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1], m[1][2] + mat.m[1][2], m[1][3] + mat.m[1][3],
        m[2][0] + mat.m[2][0], m[2][1] + mat.m[2][1], m[2][2] + mat.m[2][2], m[2][3] + mat.m[2][3],
        m[3][0] + mat.m[3][0], m[3][1] + mat.m[3][1], m[3][2] + mat.m[3][2], m[3][3] + mat.m[3][3]
    );
}
Matrix4x4 Matrix4x4::operator*(float scalar) const {
    return Matrix4x4(
        m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar, m[0][3] * scalar,
        m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar, m[1][3] * scalar,
        m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar, m[2][3] * scalar,
        m[3][0] * scalar, m[3][1] * scalar, m[3][2] * scalar, m[3][3] * scalar
    );
}
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const {
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

// matrix function
float Matrix4x4::cofactor(int r, int c) const {
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
float Matrix4x4::determinant() const {
    float result = 0.0f;
    for (int i = 0; i < 4; i++) {
        result += (m[0][i] * cofactor(0, i));
    }

    return result;
}
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
Matrix4x4 Matrix4x4::transpose() const {
    return Matrix4x4(
        m[0][0], m[1][0], m[2][0], m[3][0],
        m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2],
        m[0][3], m[1][3], m[2][3], m[3][3]
    );
};
Matrix4x4 Matrix4x4::inverse() const {
    float det_value = determinant();

    if (nearlyEqual(det_value, 0.0f)) return zero();
    else {
        Matrix4x4 adj_mat = Matrix4x4(
            cofactor(0, 0), cofactor(1, 0), cofactor(2, 0), cofactor(3, 0),
            cofactor(0, 1), cofactor(1, 1), cofactor(2, 1), cofactor(3, 1),
            cofactor(0, 2), cofactor(1, 2), cofactor(2, 2), cofactor(3, 2),
            cofactor(0, 3), cofactor(1, 3), cofactor(2, 3), cofactor(3, 3)
        );

        return adj_mat * (1.0f / det_value);
    }
}
Matrix4x4 Matrix4x4::orthogonalize() const {
    // extract row vectors 3x3 Matrix
    Vector3f r0(m[0][0], m[0][1], m[0][2]);
    Vector3f r1(m[1][0], m[1][1], m[1][2]);
    Vector3f r2(m[2][0], m[2][1], m[2][2]);

    // Modified Gram-Schmidt
    r0 = r0.normalize();

    r1 = r1 - r0 * r0.dot(r1);
    r1 = r1.normalize();

    r2 = r2 - r0 * r0.dot(r2);
    r2 = r2 - r1 * r1.dot(r2);
    r2 = r2.normalize();

    return Matrix4x4(
        r0.x, r0.y, r0.z, 0.0f,
        r1.x, r1.y, r1.z, 0.0f,
        r2.x, r2.y, r2.z, 0.0f,
        m[3][0], m[3][1], m[3][2], m[3][3]  // translation
    );
}
void Matrix4x4::printComponents() const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%12.6f\t", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Matrix4x4 Matrix4x4::rotate(Vector3f vec, float angle) const { return (*this) * makeRotation(vec, angle); }
Matrix4x4 Matrix4x4::rotateX(float angle) const { return (*this) * makeRotationX(angle); }
Matrix4x4 Matrix4x4::rotateY(float angle) const { return (*this) * makeRotationY(angle); }
Matrix4x4 Matrix4x4::rotateZ(float angle) const { return (*this) * makeRotationZ(angle); }
Matrix4x4 Matrix4x4::scale(float x, float y, float z) const { return (*this) * makeScale(x, y, z); }
Matrix4x4 Matrix4x4::scale(Vector3f vec, float k) const { return (*this) * makeScale(vec, k); }
Matrix4x4 Matrix4x4::reflect(Vector3f vec) const { return (*this) * makeReflection(vec); }
Matrix4x4 Matrix4x4::sheerXY(float s_x, float s_y) const { return (*this) * makeSheeringXY(s_x, s_y); }
Matrix4x4 Matrix4x4::sheerYZ(float s_y, float s_z) const { return (*this) * makeSheeringYZ(s_y, s_z); }
Matrix4x4 Matrix4x4::sheerXZ(float s_x, float s_z) const { return (*this) * makeSheeringXZ(s_x, s_z); }
Matrix4x4 Matrix4x4::translate(float x, float y, float z) const { return (*this) * makeTranslation(x, y, z); }
Matrix4x4 Matrix4x4::orth_proj(Vector3f vec) const { return (*this) * makeOrthoProj(vec); }
Matrix4x4 Matrix4x4::persp_proj(float d) const { return (*this) * makePerspProjZ(d); }

// rotation(affine transformation)
Matrix4x4 Matrix4x4::makeRotationX(float angle) {
    float rad = angle * 3.14159265f / 180.0f;
    float cos_value = cosf(rad);
    float sin_value = sinf(rad);

    return Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos_value, sin_value, 0.0f,
        0.0f, -sin_value, cos_value, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4x4 Matrix4x4::makeRotationY(float angle) {
    float rad = angle * 3.14159265f / 180.0f;
    float cos_value = cosf(rad);
    float sin_value = sinf(rad);

    return Matrix4x4(
        cos_value, 0.0f, -sin_value, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sin_value, 0.0f, cos_value, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4x4 Matrix4x4::makeRotationZ(float angle) {
    float rad = angle * 3.14159265f / 180.0f;
    float cos_value = cosf(rad);
    float sin_value = sinf(rad);

    return Matrix4x4(
        cos_value, sin_value, 0.0f, 0.0f,
        -sin_value, cos_value, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4x4 Matrix4x4::makeRotation(Vector3f vec, float angle) {
    Vector3f n_vec = vec.normalize();
    float rad = angle * 3.14159265f / 180.0f;
    float cos_value = cosf(rad);
    float sin_value = sinf(rad);
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
Matrix4x4 Matrix4x4::makePerspProjZ(float d) {
    return Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 1/d,
        0.0f, 0.0f, 0.0f, 0.0f
    );
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

// translation(affine transformation)
Matrix4x4 Matrix4x4::makeTranslation(float x, float y, float z) {
    return Matrix4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        x, y, z, 1.0f
    );
}