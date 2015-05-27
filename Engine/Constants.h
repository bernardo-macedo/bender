/*
 * Constants.h
 *
 *  Created on: Apr 21, 2015
 *      Author: -Bernardo
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

namespace Constants {
#ifdef __linux__
	const std::string ImgPath = "img/";
	const std::string MapPath = "map/";
	const std::string FontPath = "font/";
	const std::string audioPath = "audio/";
	const std::string ImgExtension = ".png";
#else
	const std::string ImgPath = "src/img/";
	const std::string MapPath = "src/map/";
	const std::string FontPath = "src/font/";
	const std::string audioPath = "src/audio/";
	const std::string ImgExtension = ".jpg";
#endif
	const std::string GameTitle = "Bender";
}



#endif /* CONSTANTS_H_ */
