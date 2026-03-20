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
    float     determinant() const; // 행렬식
    Matrix4x4 inverse() const;     // 역행렬 (카메라에서 핵심)

    static Matrix4x4 identity();
    static Matrix4x4 zero();
    static Matrix4x4 makeTranslation(float x, float y, float z);
    static Matrix4x4 makeScale(float x, float y, float z);
    static Matrix4x4 makeRotationX(float angle);
    static Matrix4x4 makeRotationY(float angle);
    static Matrix4x4 makeRotationZ(float angle);
    static Matrix4x4 makeRotation(Vector3f vec, float angle);
};
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
    float cos_value = cosf(angle);
    float sin_value = sinf(angle);
    float _1_sub_cos_value = 1.0f - cos_value;

    return Matrix4x4(
        vec.x * vec.x * _1_sub_cos_value + cos_value,
        vec.x * vec.y * _1_sub_cos_value + vec.z * sin_value,
        vec.x * vec.z * _1_sub_cos_value - vec.y * sin_value,
        0.0f,
        vec.x * vec.y * _1_sub_cos_value - vec.z * sin_value,
        vec.y * vec.y * _1_sub_cos_value + cos_value,
        vec.y * vec.z * _1_sub_cos_value + vec.x * sin_value,
        0.0f,
        vec.x * vec.z * _1_sub_cos_value + vec.y * sin_value,
        vec.y * vec.z * _1_sub_cos_value - vec.x * sin_value,
        vec.z * vec.z * _1_sub_cos_value + cos_value,
        0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}