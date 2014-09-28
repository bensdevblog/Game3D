class Camera
{
	private:
		float angle_of_rotation;
		float cam_x;
		float cam_y;
		float cam_z;
		float x_vector;
		float y_vector;
		float z_vector;
		float delta_angle;
		float delta_move;
		float delta_height;
		float pitch;
		float x_origin;
		float y_origin;
		boolean jumping;
		boolean developer_view;
	public:
		/* Constructor */
		Camera() { };
		
		/* Change camera direction and position */
		void computePos(float deltaMove);
		void computeDir(float deltaAngle);
		void computePitch(float deltaPitch);
		void computeHeight(float deltaHeight);
		void jump(void);

		/* Getters and setters */
		void setAngleOfRot(float aor);
		float getAngleOfRot(void);
		void setCamX(float x);
		float getCamX(void);
		void setCamY(float y);
		float getCamY(void);
		void setCamZ(float z);
		float getCamZ(void);
		void setXvector(float x_vec);
		float getXvector(void);
		void setYvector(float y_vec);
		float getYvector(void);
		void setZvector(float z_vec);
		float getZvector(void);
		void setDeltaAngle(float d_angle);
		float getDeltaAngle(void);
		void setDeltaMove(float d_move);
		float getDeltaMove(void);
		void setDeltaHeight(float d_height);
		float getDeltaHeight(void);
		void setPitch(float d_pitch);
		float getPitch(void);
		void setXorigin(float x);
		float getXorigin(void);
		void setYorigin(float y);
		float getYorigin(void);
		void jumpState(boolean jumping);
		boolean isJumping(void);
		void devState(boolean dev_view);
		boolean isDevView(void);

};

