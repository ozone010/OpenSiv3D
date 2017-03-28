//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

#include <glib-2.0/glib.h>
#include <glib-2.0/gio/gio.h>
#include <stdlib.h>
#include <string>

#include "Siv3D/FileSystem.hpp"

using namespace s3d;

std::string Linux_SpecialFolder(const int folder)
{
	const GUserDirectory folders[] = {
		G_USER_DIRECTORY_DESKTOP,
		G_USER_DIRECTORY_DOCUMENTS,
		G_USER_DIRECTORY_DOCUMENTS, //dummy
		G_USER_DIRECTORY_PICTURES,
		G_USER_DIRECTORY_MUSIC,
		G_USER_DIRECTORY_VIDEOS
	};

	std::string sf_path = "";
	if(folder == static_cast<int>(SpecialFolder::LocalAppData))
	{
		char* xch = getenv("XDG_CACHE_HOME");
		if(xch == NULL)
		{
			sf_path = getenv("HOME");
			sf_path += "/.cache";
		}
		else
			sf_path = xch;
	}
	else
		sf_path = g_get_user_special_dir(folders[folder]);

	return sf_path;
} 

bool Linux_TrashFile(const char* path)
{
	gboolean ret;
	GFile* gf = g_file_new_for_path(path);
	GError* ge;

	ret = g_file_trash(gf, nullptr, &ge);

	if(ge)
		g_error_free(ge);
	g_object_unref(gf);

	if(!ret)
		return false;

	return true;
}

# endif