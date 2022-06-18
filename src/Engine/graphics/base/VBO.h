#pragma once

namespace gr
{
	namespace base {
		/**
		 * @brief base Vertex Buffer Object class
		 * 
		 */
		class VBO
		{
		public: unsigned int ID;

		public:
			VBO(int size, const void* data);

			void Bind();
			void UnBind();
			void Delete();
		};
	}
}

