#pragma once


namespace gr
{
	namespace base {
		/**
		 * @brief base Vertex Array Object class
		 * 
		 */
		class VAO
		{
		public: unsigned int ID;

		public:
			VAO();
			void Bind();
			void UnBind();
			void Delete();
		};
	}
}

