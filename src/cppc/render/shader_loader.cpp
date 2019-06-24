#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <sys/stat.h>

using namespace std;

namespace Shader {

	static GLuint LoadAndCompileShader(const char * vertex_file_path, const char * fragment_file_path)
	{
		fprintf(stdout, "loading shaders %s and %s \n", vertex_file_path, fragment_file_path);
		bool error = false;

		struct stat vert_stat_buffer;
		if (stat(vertex_file_path, &vert_stat_buffer) != 0)
		{
			fprintf(stderr, "ERROR LOADING SHADER CODE. VERTEX FILE: %s DOES NOT EXIST OR IS EMPTY", vertex_file_path);
			error = true;
		}

		struct stat frag_stat_buffer;
		if (stat(fragment_file_path, &frag_stat_buffer) != 0)
		{
			fprintf(stderr, "ERROR LOADING SHADER CODE. FRAGMENT FILE: %s DOES NOT EXIST OR IS EMPTY", fragment_file_path);
			error = true;
		}

		if (error) { exit(EXIT_FAILURE); }

		std::ifstream vertex_stream;
		std::ifstream fragment_stream;

		std::string vertex_code;
		std::string fragment_code;

		try {
			vertex_stream = ifstream(vertex_file_path, std::ios::in | std::ios::binary);
			fragment_stream = ifstream(fragment_file_path, std::ios::in | std::ios::binary);
		}
		catch (std::ifstream::failure e)
		{
			fprintf(stderr, "SHADER_LOADER.CPP | COULD NOT CREATE IFSTREAMS");
		}

		vertex_stream.seekg(0, std::ios::end);
		vertex_code.resize(vertex_stream.tellg());
		vertex_stream.seekg(0, std::ios::beg);
		vertex_stream.read(&vertex_code[0], vertex_code.size());
		vertex_stream.close();
		const char * vertex_code_static = vertex_code.c_str();

		fragment_stream.seekg(0, std::ios::end);
		fragment_code.resize(fragment_stream.tellg());
		fragment_stream.seekg(0, std::ios::beg);
		fragment_stream.read(&fragment_code[0], fragment_code.size());
		fragment_stream.close();
		const char * fragment_code_static = fragment_code.c_str();

		unsigned int vertex_handle, fragment_handle;

		vertex_handle = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_handle, 1, &vertex_code_static, NULL);
		glCompileShader(vertex_handle);
		//checkCompileErrors(vertex, "VERTEX");

		fragment_handle = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_handle, 1, &fragment_code_static, NULL);
		glCompileShader(fragment_handle);
		//checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		GLuint ID = glCreateProgram();
		glAttachShader(ID, vertex_handle);
		glAttachShader(ID, fragment_handle);
		glLinkProgram(ID);
		//checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex_handle);
		glDeleteShader(fragment_handle);

		return ID;
	}

}