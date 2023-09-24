#include <UILy/window.h>
#include <UILy/rendering.h>
#include <UILy/debug.h>
#include <imgui/imgui.h>
#define TOOLTIP(MSG) if(ImGui::IsItemHovered()) ImGui::SetTooltip(MSG)

char videoURL[128]{};

// Video Selection
char limitBuffer[16]{};
bool limitAge = false;
int ageLimit = 10;

// Download Options
char limitRateBuffer[16]{};

// Filesystem Options
char pathsBuffer[128]{};
char outputBuffer[128]{};

// Thumnail Options
bool writeThumbnail = false;
bool writeAllThumbnail = false;

// Video Format Options
char formatBuffer[32]{};

// Post-Processing Options
bool extractAudio = false;
char audioFormatBuffer[16]{};
char remuxVideoBuffer[16]{};
char recodeVideoBuffer[16]{};
bool keepVideo = false;
char ffmpegLocationBuffer[128]{};
bool splitChapters = false;

// Misc
char otherArguments[256]{};

std::string composeCommand();

int main(int, char**)
{
	UILy::initGLFW();

	UILy::Window window(UILy::WindowState::WINDOWED, true, "yt-dlp-gui", 860, 480);


	while(window.IsOpen())
	{
		UILy::beginFrame();

		if(UILy::beginFullWindow(&window))
		{
			ImGui::InputText("URL", videoURL, 128);
			ImGui::Text("NOTE: Empty fields will use their defaults");
			if(ImGui::BeginTable("Options", 2)) {
				ImGui::TableNextColumn();
				ImGui::SeparatorText("Video Selection");

				ImGui::InputText("Max Filesize", limitBuffer, 16);
				TOOLTIP("Abort download if filesize is larger than\nSIZE, e.g. 50k or 44.6M");

				ImGui::Checkbox("Limit Age", &limitAge);
				ImGui::InputInt("Age Limit", &ageLimit);
				TOOLTIP("Download only videos suitable for the given age");

				//
				// Download Options
				//
				ImGui::SeparatorText("Download Options");

				ImGui::InputText("Limit Rate", limitRateBuffer, 16);
				TOOLTIP("Maximum download rate in bytes per second,\ne.g. 50K or 4.2M");

				//
				// Filesystem Options
				//
				ImGui::SeparatorText("Filesystem Options");

				ImGui::InputText("Paths", pathsBuffer, 128);
				TOOLTIP("[TYPES:]PATH\nThe paths where the files should be\ndownloaded. Specify the type of file and the\npath separated by a colon \":\". All the same\nTYPES as --output are supported.\nAdditionally, you can also provide \"home\"\n(default) and \"temp\" paths. All intermediary\nfiles are first downloaded to the temp path\nand then the final files are moved over to\nthe home path after download is finished.\nThis option is ignored if --output is an\nabsolute path");
				ImGui::InputText("Output", outputBuffer, 128);
				TOOLTIP("[TYPES:]TEMPLATE\nOutput filename template; see \"OUTPUT\nTEMPLATE\" for details");

				//
				// Thumbnail Options
				//
				ImGui::SeparatorText("Thumbnail Options");

				ImGui::Checkbox("Write Thumbnail", &writeThumbnail);
				TOOLTIP("Write thumbnail image to disk");
				ImGui::Checkbox("Write All Thumbnail", &writeAllThumbnail);
				TOOLTIP("Write all thumbnail image formats to disk");

				ImGui::TableNextColumn();
				//
				// Video Format Options
				//
				ImGui::SeparatorText("Video Format Options");

				ImGui::InputText("Format", formatBuffer, 32);
				TOOLTIP("Video format code, see \"FORMAT SELECTION\"\nfor more details");

				//
				// Post-Processing Options
				//
				ImGui::SeparatorText("Post-Processing Options");

				ImGui::Checkbox("Extract Audio", &extractAudio);
				TOOLTIP("Convert video files to audio-only files\n(requires ffmpeg and ffprobe)");
				ImGui::InputText("Audio Format", audioFormatBuffer, 16);
				TOOLTIP("Format to convert the audio to when -x is\nused. (currently supported: best (default),\naac, alac, flac, m4a, mp3, opus, vorbis,\nwav). You can specify multiple rules using\nsimilar syntax as --remux-video");


				ImGui::InputText("Remux Video", remuxVideoBuffer, 16);
				TOOLTIP("Remux the video into another container if\nnecessary (currently supported: avi, flv,\ngif, mkv, mov, mp4, webm, aac, aiff, alac,\nflac, m4a, mka, mp3, ogg, opus, vorbis,\nwav). If target container does not support\nthe video/audio codec, remuxing will fail.\nYou can specify multiple rules; e.g.\n\"aac>m4a/mov>mp4/mkv\" will remux aac to m4a,\nmov to mp4 and anything else to mkv");
				ImGui::InputText("Recode Video", recodeVideoBuffer, 16);
				TOOLTIP("Re-encode the video into another format if\nnecessary. The syntax and supported formats\nare the same as --remux-video");

				ImGui::Checkbox("Keep Video", &keepVideo);
				TOOLTIP("Keep the intermediate video file on disk\nafter post-processing");

				ImGui::InputText("ffmpeg Location", ffmpegLocationBuffer, 128);
				TOOLTIP("Location of the ffmpeg binary; either the\npath to the binary or its containing directory");

				ImGui::Checkbox("Split Chapters", &splitChapters);
				TOOLTIP("Split video into multiple files based on\ninternal chapters. The \"chapter:\" prefix can\nbe used with \"--paths\" and \"--output\" to set\nthe output filename for the split files. See\n\"OUTPUT TEMPLATE\" for details");

				ImGui::SeparatorText("Misc");
				ImGui::InputText("Additional Arguments", otherArguments, 256);
				TOOLTIP("Any additional arguments to pass to yt-dlp");

				ImGui::EndTable();
			}
			if(ImGui::Button("Copy Command"))
			{
				UILy::debugLog(UILy::INFO, "Copied command to clipboard");
				ImGui::SetClipboardText(composeCommand().c_str());
			}
			ImGui::DockSpace(ImGui::GetID("Console Dockspace"));
			UILy::endFullWindow();
		}

		UILy::showDebugConsole(NULL);

		UILy::endFrame();
		window.Flip();
	}

	return 0;
}

#define STRARG(VAR, NAME) if(strlen(VAR) > 0) { command += " --" NAME " "; command += VAR; }
#define BOOLARG(VAR, NAME) if(VAR) command += " --" NAME;

std::string composeCommand()
{
	std::string command = "yt-dlp";
	STRARG(limitBuffer, "max-filesize")
	if(limitAge) {
		command += " --limit-age ";
		command += std::to_string(ageLimit);
	}
	STRARG(limitRateBuffer, "limit-rate")
	STRARG(pathsBuffer, "paths")
	STRARG(outputBuffer, "output")
	BOOLARG(writeThumbnail, "write-thumbnail")
	BOOLARG(writeAllThumbnail, "write-all-thumbnail")
	STRARG(formatBuffer, "format")
	BOOLARG(extractAudio, "extract-audio")
	STRARG(audioFormatBuffer, "audio-format")
	STRARG(remuxVideoBuffer, "remux-video")
	STRARG(recodeVideoBuffer, "recode-video")
	BOOLARG(keepVideo, "keep-video")
	STRARG(ffmpegLocationBuffer, "ffmpeg-location")
	BOOLARG(splitChapters, "split-chapters")
	if(strlen(otherArguments) > 0) {
		command += " ";
		command += otherArguments;
	}

	command += " ";
	command += videoURL;
	return command;
}
