#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>

#include "opj_apps_config.h"
#include "openjpeg.h"
#include "opj_getopt.h"
#include "convert.h"
#include "format_defs.h"

#include "info_freelibrary_openjpeg_JP2Bridge.h"

void error_callback(const char *msg, void *client_data) {
	(void) client_data;
	fprintf(stdout, "[ERROR] %s", msg);
}

void warning_callback(const char *msg, void *client_data) {
	(void) client_data;
	fprintf(stdout, "[WARNING] %s", msg);
}
void info_callback(const char *msg, void *client_data) {
	(void) client_data;
	fprintf(stdout, "[INFO] %s", msg);
}

JNIEXPORT void JNICALL Java_info_freelibrary_openjpeg_JP2Bridge_encode(
		JNIEnv *env, jobject aCallingObj, jobject aEncodingObj) {
	opj_stream_t *l_stream = 00;
	opj_codec_t* l_codec = 00;
	opj_image_t *image = NULL;
	opj_cparameters_t parameters;
	raw_cparameters_t raw_cp;

	OPJ_UINT32 l_nb_tiles = 4;
	OPJ_BOOL success;

	const char *decoding_exception =
			"info/freelibrary/openjpeg/DecodingException";
	const char *encoding_exception =
			"info/freelibrary/openjpeg/EncodingException";

	/* set encoding parameters to default values */
	opj_set_default_encoder_parameters(&parameters);

	/* start of JP2Encoding processing */

	jclass encoding = (*env)->GetObjectClass(env, aEncodingObj);

	jmethodID getInputFile = (*env)->GetMethodID(env, encoding, "getInputFile", "()Ljava/lang/String;");
	jmethodID getOutputFile = (*env)->GetMethodID(env, encoding, "getOutputFile", "()Ljava/lang/String;");
	jmethodID getSourceFormat = (*env)->GetMethodID(env, encoding, "getSourceFormat", "()I");
	jmethodID getTargetFormat = (*env)->GetMethodID(env, encoding, "getTargetFormat", "()I");

	jstring inFileStr = (jstring)(*env)->CallObjectMethod(env, aEncodingObj, getInputFile);
	jstring outFileStr = (jstring)(*env)->CallObjectMethod(env, aEncodingObj, getOutputFile);
	jint sourceExt = (*env)->CallIntMethod(env, aEncodingObj, getSourceFormat);
	jint targetExt = (*env)->CallIntMethod(env, aEncodingObj, getTargetFormat);

	const char *inFile = (*env)->GetStringUTFChars(env, inFileStr, 0);
	strncpy(parameters.infile, inFile, sizeof(parameters.infile)-1);
	(*env)->ReleaseStringUTFChars(env, inFileStr, inFile);

	const char *outFile = (*env)->GetStringUTFChars(env, outFileStr, 0);
	strncpy(parameters.outfile, outFile, sizeof(parameters.outfile)-1);
	(*env)->ReleaseStringUTFChars(env, outFileStr, outFile);

	parameters.decod_format = (int) sourceExt;
	parameters.cod_format = (int) targetExt;

	fprintf(stdout, "parameter.infile: %s\n", parameters.infile);
	fprintf(stdout, "parameter.outfile: %s\n", parameters.outfile);
	fprintf(stdout, "parameter.decod_format: %d\n", parameters.decod_format);
	fprintf(stdout, "parameter.cod_format: %d\n", parameters.cod_format);
	fprintf(stdout, "sourceExt: %d\n", sourceExt);
	fprintf(stdout, "targetExt: %d\n", targetExt);

	parameters.tile_size_on = OPJ_FALSE;

	parameters.tcp_numlayers = 0;
	/* if no rate entered, lossless by default */
	if (parameters.tcp_numlayers == 0) {
		parameters.tcp_rates[0] = 0;	/* MOD antonin : losslessbug */
		parameters.tcp_numlayers++;
		parameters.cp_disto_alloc = 1;
	}

//	if((parameters.cp_tx0 > parameters.image_offset_x0) || (parameters.cp_ty0 > parameters.image_offset_y0)) {
//		fprintf(stderr,
//			"Error: Tile offset dimension is inappropriate --> TX0(%d)<=IMG_X0(%d) TYO(%d)<=IMG_Y0(%d) \n",
//			parameters.cp_tx0, parameters.image_offset_x0, parameters.cp_ty0, parameters.image_offset_y0);
//		//return 1;
//	}
//
//	int i;
//	for (i = 0; i < parameters.numpocs; i++) {
//		if (parameters.POC[i].prg == -1) {
//			fprintf(stderr,
//				"Unrecognized progression order in option -P (POC n %d) [LRCP, RLCP, RPCL, PCRL, CPRL] !!\n",
//				i + 1);
//		}
//	}

	//parameters->cp_disto_alloc = 1;

//	parameters.cp_tx0 = 0;
//	parameters.cp_ty0 = 0;
//	parameters.cp_tdx = 512;
//	parameters.cp_tdy = 512;

	/* end of JP2Encoding processing */

	/* Create comment for codestream */
	if (parameters.cp_comment == NULL ) {
		const char comment[] = "Created by OpenJPEG version ";
		const size_t clen = strlen(comment);
		const char *version = opj_version();

		parameters.cp_comment = (char*) malloc(clen + strlen(version) + 1);
	}

	switch (parameters.decod_format) {
	case PGX_DFMT:
		image = pgxtoimage(parameters.infile, &parameters);
		if (!image) {
			(*env)->ThrowNew(env, (*env)->FindClass(env, decoding_exception),
					"Failed to convert PGX image");
		}
		break;
	case PXM_DFMT:
		image = pnmtoimage(parameters.infile, &parameters);
		if (!image) {
			(*env)->ThrowNew(env, (*env)->FindClass(env, decoding_exception),
					"Failed to convert PNM image");
		}
		break;
	case BMP_DFMT:
		image = bmptoimage(parameters.infile, &parameters);
		if (!image) {
			(*env)->ThrowNew(env, (*env)->FindClass(env, decoding_exception),
					"Failed to convert BMP image");
		}
		break;
	case TIF_DFMT:
		image = tiftoimage(parameters.infile, &parameters);
		if (!image) {
			(*env)->ThrowNew(env, (*env)->FindClass(env, decoding_exception),
					"Failed to convert TIF image");
		}
		break;
	case RAW_DFMT:
		image = rawtoimage(parameters.infile, &parameters, &raw_cp);
		if (!image) {
			(*env)->ThrowNew(env, (*env)->FindClass(env, decoding_exception),
					"Failed to convert RAW image");
		}
		break;
	case RAWL_DFMT:
		image = rawltoimage(parameters.infile, &parameters, &raw_cp);
		if (!image) {
			(*env)->ThrowNew(env, (*env)->FindClass(env, decoding_exception),
					"Failed to convert RAW image");
		}
		break;
	case TGA_DFMT:
		image = tgatoimage(parameters.infile, &parameters);
		if (!image) {
			(*env)->ThrowNew(env, (*env)->FindClass(env, decoding_exception),
					"Failed to convert TGA image");
		}
		break;
	case PNG_DFMT:
		image = pngtoimage(parameters.infile, &parameters);
		if (!image) {
			(*env)->ThrowNew(env, (*env)->FindClass(env, decoding_exception),
					"Failed to convert PNG image");
		}
		break;
	default:
		(*env)->ThrowNew(env, (*env)->FindClass(env, decoding_exception),
				"Trying to decode an unsupported format");
		break;
	}

	switch (parameters.cod_format) {
	case J2K_CFMT: { /* JPEG-2000 codestream */
		l_codec = opj_create_compress(OPJ_CODEC_J2K);
		break;
	}
	case JP2_CFMT: { /* JPEG 2000 compressed image data */
		l_codec = opj_create_compress(OPJ_CODEC_JP2);
		break;
	}
	default:
		(*env)->ThrowNew(env, (*env)->FindClass(env, encoding_exception),
				"Trying to encode to something other JP2/J2K");
		break;
	}

	/* Decide if MCT should be used */
	//parameters.tcp_mct = image->numcomps == 3 ? 1 : 0;

	/* set up to catch events using our callbacks and give a local context */
	opj_set_info_handler(l_codec, info_callback, 00);
	opj_set_warning_handler(l_codec, warning_callback, 00);
	opj_set_error_handler(l_codec, error_callback, 00);

	opj_setup_encoder(l_codec, &parameters, image);

	l_stream = opj_stream_create_default_file_stream_v3(parameters.outfile,
			OPJ_FALSE);
	if (!l_stream) {
		(*env)->ThrowNew(env, (*env)->FindClass(env, encoding_exception),
				"Unable to create default output file stream");
	}

	success = opj_start_compress(l_codec, image, l_stream);
	if (!success) {
		(*env)->ThrowNew(env, (*env)->FindClass(env, encoding_exception),
				"Failed to encode image (couldn't start compression)");
	}

	/*if (parameters.tile_size_on) {
		unsigned int i;
		char *message;

		OPJ_BYTE *l_data;
		OPJ_UINT32 l_data_size = 512 * 512 * 3;

		l_data = (OPJ_BYTE*) malloc(l_data_size * sizeof(OPJ_BYTE));
		memset(l_data, 0, l_data_size);
		assert(l_data);

		for (i = 0; i < l_nb_tiles; ++i) {
			if (!opj_write_tile(l_codec, i, l_data, l_data_size, l_stream)) {
				opj_stream_destroy_v3(l_stream);
				opj_destroy_codec(l_codec);
				opj_image_destroy(image);

				sprintf(message, "Failed to write the tile: %d", i);
				(*env)->ThrowNew(env,
						(*env)->FindClass(env, encoding_exception), message);
			}
		}

		free(l_data);
	} else { */
		success = opj_encode(l_codec, l_stream);
		if (!success) {
			(*env)->ThrowNew(env, (*env)->FindClass(env, encoding_exception),
					"Failed to encode image (without using tiles)");
		}
	/* } */

	success = opj_end_compress(l_codec, l_stream);
	if (!success) {
		opj_stream_destroy_v3(l_stream);
		opj_destroy_codec(l_codec);
		opj_image_destroy(image);

		(*env)->ThrowNew(env, (*env)->FindClass(env, encoding_exception),
				"Failed to encode image");
	}

	/* close and free the byte stream */
	opj_stream_destroy_v3(l_stream);

	/* free remaining compression structures */
	opj_destroy_codec(l_codec);

	/* free image data */
	opj_image_destroy(image);

	/* free user parameters structure */
	if (parameters.cp_comment) {
		free(parameters.cp_comment);
	}

	if (parameters.cp_matrice) {
		free(parameters.cp_matrice);
	}
}

JNIEXPORT void JNICALL Java_info_freelibrary_openjpeg_JP2Bridge_decode(
		JNIEnv *env, jobject aCallingObj, jobjectArray aDecodingObj) {
	printf("Hello Decoder!\n");
}

