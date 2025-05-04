// Difinition.h


//// *************************** < 메뉴 관련 함수 정의부 > *************************** ////
// 메뉴 UI
void printMenu() {
	puts("\n");
	puts("\t\t\t===========================================================================");
	puts("\t\t\t                  ### 그레이 영상처리 Ver 1.0 (RC 4) ###\n");
	puts("\t\t\t---------------------------------------------------------------------------");
	puts("\t\t\t [ 파일 메뉴 선택 ] \t 1.열기  2.저장  0.종료 \n\n");
	puts("\t\t\t [ 영상처리 메뉴 선택 ] \n");
	puts("\t\t\t    A.밝기  B.선명도  C.반전  D.흑백  E.비트연산  F.감마변환  G.범위강조");
	puts("\t\t\t    H.파라볼라 변환  I.스트래칭     J.미러링  K.회전  L.확대/축소  M.이동");
	puts("\t\t\t===========================================================================\n");
	printf("\t\t\t  선택한 파일명 : %s", imgName);
}
// 메뉴 선택
void choiceMenu() {
	printMenu();
	printf("\t\t\t 메뉴 선택 : ");

	while (inKey != '0') {
		inKey = _getch();

		switch (inKey) {
		case '0':	free2D(inImage, inH); free2D(outImage, outH);	break;		// 종료
		case '1':				// 파일 open
			system("cls");	printMenu();	openImage();	break;
		case '2':
			saveImage();	break;

		case 'A':	case 'a':	// 밝기 조절
			system("cls");	printMenu();	brightControlImage();	break;
		case 'B':	case 'b':	// 선명도 조절
			system("cls");	printMenu();	clearControlImage();	break;
		case 'C':	case 'c':	// 반전 조절
			system("cls");	printMenu();	reverseImage();	break;
		case 'D':	case 'd':	// 흑백 (128/평균)
			system("cls");	printMenu();	grayScaleImage();	break;
		case 'E':	case 'e':	// 비트 연산 (And/Or/Xor/Not)
			system("cls");	printMenu();	bitCalcImage();	break;
		case 'F':	case 'f':	// 감마 변환
			system("cls");	printMenu();	gammaConverseImage();	break;
		case 'G':	case 'g':	// 범위 강조 
			system("cls");	printMenu();	rangeEmphasisImage();	break;
		case 'H':	case 'h':	// 파라볼라 변환 
			system("cls");	printMenu();	parabolaImage();	break;
		case 'I':	case 'i':		// 스트래칭
			system("cls");	printMenu();	stretchedImage();	break;

		case 'J':	case 'j':		// 미러링 (좌우/상하/좌우+상하)
			system("cls");	printMenu();	mirroringImage();	break;
		case 'K':	case 'k':	// 회전 (방향, 90/180/270도/자유)
			system("cls");	printMenu();	turnImage();	break;
		case 'L':	case 'l':		// 이미지 크기(규격) 확대/축소
			system("cls");	printMenu();	imageSizeUpDown();	break;	//doubleUpDownImage();	break;
		case 'M':	case 'm':	// 이미지 이동
			system("cls");	printMenu();	moveImage();	break;

		default:				// 예외처리
			printf("입력 오류! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			printMenu();
		}
	}
}
//// ********************************************************************************* ////



//// ************************* < 이미지 입출력 함수 정의부 > ************************* ////
// 2차원 배열 생성 함수 (동적할당)
unsigned char** malloc2D(int row, int col) {
	unsigned char** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당. 
	retMemory = (unsigned char**)malloc(row * sizeof(unsigned char*));					// unsigned char 뒤에 * 잊지 말기!
	for (int i = 0; i < row; i++) {				// 가로 픽셀, 세로 픽셀 바뀔 때 범위 주의!
		retMemory[i] = (unsigned char*)malloc(col * sizeof(unsigned char));
	}
	return retMemory;
}
// free 함수			// 프로그램 종료시 실행
void free2D(unsigned char** memory, int h) {
	for (int i = 0; i < h; i++) {
		free(memory[i]);
	}
	free(memory);
}
// 출력 free 함수			// 함수 실행 시 실행
void free2D_out() {
	if (outImage == NULL)
		return;

	for (int i = 0; i < outH; i++)
		free(outImage[i]);
	free(outImage);
}
// 1.이미지 파일 열기 (입력)
void openImage() {
	char fullName[100] = "C:/images/Gallery/Gallery";			// C:/images/Pet_RAW(squre)/Pet_RAW(512x512)/";

	printf("\t\t\t 파일명 --> ");	// cat01, dog13
	scanf("%s", imgName);

	while (1) {
		printf("\n\t\t\t\t\t\t\t\t\t[픽셀 선택] \n");
		printf("\n\t\t\t\t\t\t\t\t\t  1.128  2.256  3.512 ");

		inKey = _getch();
		switch (inKey) {
		case '1':		// 128x128
			pix = 1;
			inW = 128, inH = 128;

			// 주소(fullName) + 파일명(imgName) + _128.raw 더해서 --> filePath로
			strcat(fullName, "(128x128)/");		// strcat : 문자열을 이어줌
			strcat(fullName, imgName);
			strcat(fullName, "_128.raw");
			strcat(imgName, "_128.raw");

			strcpy(filePath, fullName);

			break;
		case '2':		// 256x256
			pix = 2;
			inW = 256, inH = 256;

			strcat(fullName, "(256x256)/");
			strcat(fullName, imgName);
			strcat(fullName, "_256.raw");
			strcat(imgName, "_256.raw");

			strcpy(filePath, fullName);

			break;
		case '3':		// 512x512
			pix = 3;
			inW = 512, inH = 512;

			strcat(fullName, "(512x512)/");
			strcat(fullName, imgName);
			strcat(fullName, "_512.raw");
			strcat(imgName, "_512.raw");

			strcpy(filePath, fullName);

			break;
		default:
			printf("\n\n\t\t\t\t\t\t\t\t\t입력 오류! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			printMenu();	printf("\t\t\t 파일명 --> ");
		}
		if (pix != 0) break;
	}

	//// 파일 열기 ////
	FILE* rfp = fopen(filePath, "rb");		// rb: Read Binary
	if (rfp == NULL)		// 오류 처리
		return;

	// 입력 영상의 크기를 알아내는 코드. --> inH, inW 결정
	fseek(rfp, 0L, SEEK_END);		// 파일의 끝으로 이동
	unsigned long fsize = ftell(rfp);			// 너 어디야?    262144(=512x512)
	fclose(rfp);

	inH = inW = sqrt(fsize);			// (아주 중요!) 픽셀 수 파악하는 코드
	// 입력영상 (inImage)의 메모리 할당
	inImage = malloc2D(inH, inW);

	// 파일 --> 메모리로 로딩
	rfp = fopen(filePath, "rb");
	for (int i = 0; i < inH; i++) {
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	}

	//// 파일 닫기 ////
	fclose(rfp);

	system("cls");
	printMenu();
	printf("\n\n");

	ori_printScreen();
}
// 2.출력 이미지 저장 함수
void saveImage() {
	char fullName[100] = "C:/images/Gallery/Gallery";			// C:/images/Pet_RAW(squre)/Pet_RAW(512x512)/";

	system("cls");
	printMenu();
	printf("\t\t\t (저장) 파일명 --> ");	// cat01, dog13
	scanf("%s", imgName);

	while (1) {
		printf("\n\t\t\t\t\t\t\t\t\t[(저장) 픽셀 선택] \n");
		printf("\n\t\t\t\t\t\t\t\t\t  1.128  2.256  3.512  0.저장 취소 ");

		inKey = _getch();
		switch (inKey) {
		case '1':		// 128x128
			pix = 1;
			inW = 128, inH = 128;

			// 주소(fullName) + 파일명(imgName) + _128.raw 더해서 --> filePath로
			strcat(fullName, "(128x128)/");		// strcat : 문자열을 이어줌
			strcat(fullName, imgName);
			strcat(fullName, "_128.raw");
			strcat(imgName, "_128.raw");

			strcpy(filePath, fullName);

			break;
		case '2':		// 256x256
			pix = 2;
			inW = 256, inH = 256;

			strcat(fullName, "(256x256)/");
			strcat(fullName, imgName);
			strcat(fullName, "_256.raw");
			strcat(imgName, "_256.raw");

			strcpy(filePath, fullName);

			break;
		case '3':		// 512x512
			pix = 3;
			inW = 512, inH = 512;

			strcat(fullName, "(512x512)/");
			strcat(fullName, imgName);
			strcat(fullName, "_512.raw");
			strcat(imgName, "_512.raw");

			strcpy(filePath, fullName);

			break;
		default:
			printf("\n\n\t\t\t\t\t\t\t\t\t저장 실패! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			printMenu();	printf("\t\t\t (저장) 파일명 --> ");
		}
		if (pix != 0) break;
	}

	//// 파일 열기 ////
	FILE* wfp = fopen(filePath, "wb");		// wb: Write Binary
	if (wfp == NULL)		// 오류 처리
		return;

	// 메모리 --> 파일로 로딩
	for (int i = 0; i < outH; i++) {
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	}

	//// 파일 닫기 ////
	fclose(wfp);
	if (inKey == '1' || inKey == '2' || inKey == '3') {
		MessageBox(hwnd, L"저장 OK", L"저장 창", NULL);
	}
	else 
		MessageBox(hwnd, L"저장 실패", L"저장 창", NULL);

	system("cls");
	printMenu();
	printf("\n\n");

	ori_printScreen();
}

// 원본 이미지
void originImage(char oriImage) {
	// Original 128x128
	if (oriImage == 1) 
		inImg_128();
	// Original 256x256
	else if (oriImage == 2) 
		inImg_256();
	// Original 512x512
	else if (oriImage == 3) 
		inImg_512();
	else
		printf("파일 업로드 오류! \n");
}
// 결과 이미지
void resultImage(char oriImage) {
	// 원본 사이즈로 출력
	if (imgSize == 0) {
		// Result 128x128
		if (oriImage == 1)
			outImg_128();
		// Result 256x256
		else if (oriImage == 2)
			outImg_256();
		// Result 512x512
		else if (oriImage == 3)
			outImg_512();
		else
			printf("파일 업로드 오류!");
	}
	// 2배 확대 출력
	else if (imgSize == 1) {
		// Result 128x128
		if (oriImage == 1)
			outImg_128();
		// Result 256x256
		else if (oriImage == 2)
			outImg_256();
		// Result 512x512
		else if (oriImage == 3)
			outImg_512();
		else
			printf("파일 업로드 오류!");
	}
	// 2배 축소 출력
	else if (imgSize == 2) {
		// Result 128x128
		if (oriImage == 1)
			outImg_128();
		// Result 256x256
		else if (oriImage == 2)
			outImg_256();
		// Result 512x512
		else if (oriImage == 3)
			outImg_512();
		else
			printf("파일 업로드 오류!");
	}
	else
		printf("파일 입력 오류!");
}
// 원본 이미지 화면 출력
void ori_printScreen() {
	if (pix == 1)	originImage(1);		// 128x128
	else if (pix == 2)	originImage(2);		// 256x256
	else if (pix == 3)	originImage(3);		// 512x512
}
// 결과 이미지 화면 출력
void res_printScreen() {
	if (pix == 1)	resultImage(1);		// 128x128
	else if (pix == 2)	resultImage(2);		// 256x256
	else if (pix == 3)	resultImage(3);		// 512x512
}
//// ********************************************************************************* ////



//// ************************* < 희소점 처리 기능 함수 정의부 > ********************** ////
// A.이미지 밝기 값 조절
void brightControlImage() {
	// *******함수마다 붙이기******** //
	free2D_out(); 

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);
	// ****************************** // 

	inImgCheck();

	system("cls");
	printMenu();

	int value;

	printf("\t\t  밝기 조절 값 --> ");
	scanf_s("%d", &value);
	printf("\n");

	ori_printScreen();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[i][k] + value;		// px : pixel

			if (px > 255)
				px = 255;
			else if (px < 0)
				px = 0;

			outImage[i][k] = px;
		}
	}
	if (value > 0) 
		printf("\t\t\t < 밝기 %d 증가 화면 >", value);
	else if (value < 0) 
		printf("\t\t\t < 밝기 %d 감소 화면 >", value);
	else 
		printf("다시 입력하세요!\n");
	res_printScreen();
}

// B.이미지 선명도 조절
void clearControlImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();

	int value = 0;

	printf("\t\t\t[선명도 조절] \n");
	printf("\n\t\t\t\t\t\t\t\t\t  1.선명하게  2.희미하게");

	inKey = _getch();
	if (inKey == '1') {
		printf("\n\n\t\t\t\t\t\t\t\t\t 선명도 조절 값(양수) --> ");
		scanf_s("%d", &value);

		while (1) {
			if (value > 0) {
				break;
			}
			else
				printf("\n\t\t\t\t\t\t\t 입력오류! 양수를 다시 입력하세요! \n");
		}
	}
	else if (inKey == '2') {
		printf("\n\n\t\t\t\t\t\t\t\t\t 선명도 조절 값(양수) --> ");
		scanf_s("%d", &value);

		while (1) {
			if (value > 0) {
				break;
			}
			else
				printf("\n\t\t\t\t\t\t\t 입력오류! 양수를 다시 입력하세요! \n");
		}
	}
	else
		printf("\t\t 다시 입력하세요! \n");

	switch (inKey) {
	case '1':		// 선명하게
		clearUp(value);
		break;
	case '2':		// 희미하게
		clearDown(value);
		break;
	default:
		printf("입력 오류! 재입력 바랍니다! \n");
		Sleep(1000);	system("cls");
		printMenu();	printf("\t\t\t 파일명 --> ");
		break;
	}
}

// C.이미지 반전 처리
void reverseImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();
	printf("\n\n");

	ori_printScreen();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[i][k];

			outImage[i][k] = 255 - px;
		}
	}
	printf("\t\t\t < 영상 반전 화면 > ");
	res_printScreen();
}

// D.이미지 흑백 처리
void grayScaleImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();

	printf("\t\t  1.128 기준  2.평균값 기준 \n\n");

	ori_printScreen();

	inKey = _getch();
	switch (inKey) {
	case '1':		// 128 기준
		grayScale128();
		break;
	case '2':		// 평균값 기준
		grayScaleAvg();
		break;
	default:
		printf("다시 입력하세요! \n");
		break;
	}
}

// E.비트연산 (And/Or/Xor/Not)
void bitCalcImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();

	int value = 0;

	printf("\t\t 1.And  2.Or  3.Xor  4.Not ");

	inKey = _getch();
	if (inKey == '1' || inKey == '2' || inKey == '3') {
		while (1) {
			printf("\n\n\t\t\t\t\t\t\t\t 연산할 값 (0 or 255) : ");
			scanf_s("%d", &value);

			if (0 <= value && value <= 255) {
				break;
			}
			else
				printf("\n\t\t\t\t\t\t\t 입력오류! 값(0~255)을 다시 입력하세요! \n");
		}
	}
	system("cls");
	printMenu();
	printf("\n\n");

	ori_printScreen();

	switch (inKey) {
	case '1':
		bitCalc_And(value);
		break;
	case '2':
		bitCalc_Or(value);
		break;
	case '3':
		bitCalc_Xor(value);
		break;
	case '4':
		bitCalc_Not();
		break;
	default:
		printf("다시 입력하세요! \n");
		break;
	}


}

// 예외 처리 확인
// F.감마 변환
void gammaConverseImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	// 출력 변수 설정
	outH = inH;
	outW = inW;
	// 출력 이미지 동적 할당
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();

	float value = 0;

	printf("\t\t   감마 값 입력 : ");
	scanf_s("%f", &value);

	ori_printScreen();

	if (value != 0)
		for (int i = 0; i < inH; i++)
			for (int k = 0; k < inW; k++) {
				//	outImage[i][k] = pow((inImage[i][k] / 255), value) * 255 + 0.5;
				float gamma = pow(float(inImage[i][k]), 1/value);
				if (gamma > 255)
					outImage[i][k] = 255;
				else if (gamma < 0)
					outImage[i][k] = 0;
				else
					outImage[i][k] = gamma;
			}
	else
		printf("다시 입력하세요! \n");
	printf("\t\t\t < 감마 변환(%.1f) 화면 > ", value);
	res_printScreen();
}

// G.범위 강조
void rangeEmphasisImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

}

// H.파라볼라 변환
void parabolaImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();


}

// I.스트래칭
void stretchedImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

}
//// ********************************************************************************* ////



//// ************************** < 기하학 처리 함수 정의부 > ************************** ////
// J.미러링 (좌우/상하/좌우+상하) 
void mirroringImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();

	printf("\t\t 1.좌우  2.상하  3.상하+좌우 \n\n");

	ori_printScreen();

	inKey = _getch();
	switch (inKey) {
	case '1':
		L_R_mirroring();
		break;
	case '2':
		T_B_mirroring();
		break;
	case '3':
		TB_LR_mirroring();
		break;
	default:
		printf("다시 입력하세요! \n");
		break;
	}
	res_printScreen();
}

// K.회전(오른쪽,왼쪽 90/180/270/자유-백워딩+중앙)
void turnImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();

	int direct = 0;

	printf("\t\t [방향] 1.오른쪽  2.왼쪽 ");
	scanf_s("%d", &direct);

	// 시계방향 회전
	if (direct == 1) {
		printf("\n\t\t\t\t\t\t\t\t    [각도_시계방향] A.90  B.180  C.270  D.자유 ");
		inKey = _getch();
		switch (inKey) {
		case 'A':	case 'a':		// 90도 회전
			system("cls");	printMenu();	turn90Right();	break;
		case 'B':	case 'b':		// 180도 회전
			system("cls");	printMenu();	turn180Right();	break;
		case 'C':	case 'c':		// 270도 회전
			system("cls");	printMenu();	turn270Right();	break;
//		case 'D':	case 'd':		// 자유 회전
//			system("cls");	printMenu();	turn270Right();	break;
		default:
			break;
		}
	}
	// 반시계방향 회전
	else if (direct == 2) {
		printf("\n\t\t\t\t\t\t\t\t    [각도_반시계방향] A.90  B.180  C.270  D.자유 ");
		inKey = _getch();
		switch (inKey) {
		case 'A':	case 'a':		// 90도 회전
			system("cls");	printMenu();	turn90Left();	break;
		case 'B':	case 'b':		// 180도 회전 
			system("cls");	printMenu();	turn180Left();	break;
		case 'C':	case 'c':		// 270도 회전
			system("cls");	printMenu();	turn270Left();	break;
//		case 'D':	case 'd':		// 자유 회전
//			system("cls");	printMenu();	turn270Left();	break;
		default:
			break;
		}
	}
	/*
	else if (direct == 3) {
		int angle;
		printf("\n\t\t\t\t\t\t\t\t회전 각도 --> ");
		scanf("%d", &angle);

		while (1) {
			if (angle > 0) {
				break;
			}
			else {
				printf("\n\t\t\t\t\t\t\t 입력오류! 양수를 다시 입력하세요! \n");
			}
		}

		switch (inKey) {
			system("cls");
			printMenu();
			printf("\n\n");
			ori_printScreen();
		case '1':		// 선명하게
			turnFree(angle);
			break;
		case '2':		// 희미하게
			turnFreeCenter(angle);
			break;
		default:
			printf("\n\t\t\t\t\t\t\t 입력 오류! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			printMenu();	printf("\t\t\t 파일명 --> ");
			break;
		}
	}
	*/
	else {
		printf("\t\t다시 입력해주세요! \n");
		return;
	}
	res_printScreen();
}

// L.이미지 크기(규격) 확대/축소
void imageSizeUpDown() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();

	int scale = 0;

	printf("\n\n\t\t\t 1.이미지 크기 확대 (포워딩)   2.이미지 크기 확대 (백워딩) ");
	printf("\n\n\t\t\t 3.이미지 크기 축소 (포워딩)   4.이미지 크기 축소 (백워딩) ");

	inKey = _getch();
	if (inKey == '1' || inKey == '2') {
		printf("\n\n\t\t\t\t\t\t\t\t 이미지 확대 배율 : ");
		scanf("%d", &scale);

		while (1) {
			if (scale > 0) {
				break;
			}
			else
				printf("\n\t\t\t\t\t\t\t 입력오류! 양수를 다시 입력하세요! \n");
		}
	}
	else if (inKey == '3' || inKey == '4') {
		printf("\n\n\t\t\t\t\t\t\t\t 이미지 축소 배율 : ");
		scanf("%d", &scale);

		while (1) {
			if (scale > 0) {
				break;
			}
			else
				printf("\n\t\t\t\t\t\t\t 입력오류! 양수를 다시 입력하세요! \n");
		}
	}
	else 
		printf("\t\t 다시 입력하세요! \n");

	system("cls");
	printMenu();
	printf("\n\n");
	ori_printScreen();

	switch (inKey) {
	case '1':	sizeUp(scale);	break;
	case '2':	backwardMappingSizeUp(scale);		break;
	case '3':	sizeDown(scale);	break;
	case '4':	backwardMappingSizeDown(scale);		break;
	default:		printf("\t\t다시 입력하세요! \n");	break;
	}
	res_printScreen();
}

// L.2배 확대/축소
/*
void doubleUpDownImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();

	printf("\t\t 1.2배 확대  2.2배 축소 ");

	ori_printScreen();

	inKey = _getch();
	switch (inKey) {
	case '1':
		doubleUp();
		break;
	case '2':
		doubleDown();
		break;
	default:
		printf("다시 입력하세요! \n");
		break;
	}
	res_printScreen();
}
*/

// M.이동
void moveImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	system("cls");
	printMenu();

	int value = 0;

	printf("\t\t  이동할 값 : ");
	scanf("%d", &value);

	ori_printScreen();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 0;
		}
	}
	for (int i = 0; i < inH - value; i++) {
		for (int k = 0; k < inW - value; k++) {
			outImage[i][k] = inImage[i + value][k + value]; // = inImage[i][k];
		}
	}
	res_printScreen();
}
//// ********************************************************************************* ////



//// *************************** < 결과 처리 함수 정의부 > *************************** ////
// 입력 이미지 입력 여부 확인
void inImgCheck() {
	if (inImage == NULL)
	{
		printf("\t\t\t 입력 이미지 없음 \n");
		return;
	}
}

// 이미지 파일 입력_128x128
void inImg_128() {
	short px = 0;
	printf("\n\t\t\t < 원본 이미지 화면(128) > ");
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			px = inImage[i][k];
			SetPixel(hdc, k + 300, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 입력_256x256
void inImg_256() {
	short px = 0;
	printf("\n\t\t\t < 원본 이미지 화면(256) > ");
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			px = inImage[i][k];
			SetPixel(hdc, k + 250, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 입력_512x512
void inImg_512() {
	short px = 0;
	printf("\n\t\t < 원본 이미지 화면(512) > ");
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			px = inImage[i][k];
			SetPixel(hdc, k + 50, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 출력_128x128
void outImg_128() {
	short px = 0;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			px = outImage[i][k];
			SetPixel(hdc, k + 800, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 출력_256x256
void outImg_256() {
	short px = 0;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			px = outImage[i][k];
			SetPixel(hdc, k + 720, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 출력_512x512
void outImg_512() {
	short px = 0;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			px = outImage[i][k];
			SetPixel(hdc, k + 600, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}

// B.선명하게
void clearUp(int val) {
	system("cls");
	printMenu();
	printf("\n\n");
	ori_printScreen();

	if (val > 0) {
		for (int i = 0; i < inH; i++) {
			for (int k = 0; k < inW; k++) {
				int px = inImage[i][k] * val;		// px : pixel

				if (px > 255)
					outImage[i][k] = 255;
				else
					outImage[i][k] = px;
			}
		}
		printf("\t\t\t< 선명도 %d 증가 화면 >", val);
		res_printScreen();
	}
	else
		printf("\t\t\t음수 또는 0 입력.. 양수를 입력해주세요.");
}
// B.흐릿하게
void clearDown(int val) {
	system("cls");
	printMenu();
	printf("\n\n");
	ori_printScreen();

	if (val > 0) {
		for (int i = 0; i < inH; i++) {
			for (int k = 0; k < inW; k++) {
				int px = inImage[i][k] / val;		// px : pixel

				if (px > 255)
					outImage[i][k] = 255;
				else
					outImage[i][k] = px;
			}
		}
		printf("\t\t\t< 선명도 %d 감소 화면 >", val);
		res_printScreen();
	}
	else
		printf("\t\t\t음수 또는 0 입력.. 양수를 입력해주세요.");
}

// D.흑백처리 (128 기준)
void grayScale128() {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[i][k];

			if (px > 128) {
				px = 255;
			}
			else if (px <= 128) {
				px = 0;
			}
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < 영상 흑백 처리(128 기준) 화면 > ");
	res_printScreen();
}
// D.흑백처리 (평균값 기준)
void grayScaleAvg() {
	int pixelSum = 0;
	int pixelAvg = 0;

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[i][k];
			pixelSum += px;
		}
	}
	pixelAvg = pixelSum / (inH * inW);

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[i][k];
			if (px > pixelAvg) {
				px = 255;
			}
			else {
				px = 0;
			}
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < 영상 흑백 처리(평균값 %d 기준) 화면 > ", pixelAvg);
	res_printScreen();
}

// E-1.비트연산_And
void bitCalc_And(int val) {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			unsigned char px = inImage[i][k] & val;

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < AND 비트 연산 화면 > ");
	res_printScreen();
}
// E-2.비트연산_Or
void bitCalc_Or(int val) {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			unsigned char px = inImage[i][k] | val;
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < OR 비트 연산 화면 > ");
	res_printScreen();
}
// E-3.비트연산_Xor
void bitCalc_Xor(int val) {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			unsigned char px = inImage[i][k] ^ val;
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < XOR 비트 연산 화면 > ");
	res_printScreen();
}
// E-4.비트연산_Not
void bitCalc_Not() {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			unsigned char px = ~inImage[i][k];
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < NOT 비트 연산 화면 > ");
	res_printScreen();
}

// J.이미지 좌우 미러링
void L_R_mirroring() {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[i][inW - 1 - k];	// (최대열 - 1) - 반복자

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < 영상 좌우 미러링 화면 > ");
}
// J.이미지 상하 미러링
void T_B_mirroring() {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[inH - 1 - i][k];		// (최대행 - 1) - 반복자

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < 영상 상하 미러링 화면 > ");
}
// J.이미지 상하+좌우 미러링
void TB_LR_mirroring() {
	for (int i = 0; i < inW; i++) {
		for (int k = 0; k < inH; k++) {
			int mirror_i = inH - 1 - i;
			int mirror_k = inW - 1 - k;

			outImage[i][k] = inImage[mirror_i][mirror_k];
		}
	}
	printf("\t\t\t < 영상 상하/좌우 미러링 화면 > ");
}

// K.결과 이미지 시계방향으로 90도 회전
void turn90Right() {
	printf("\n\n");
	ori_printScreen();

	for (int i = 0; i < inW; i++) {
		for (int k = 0; k < inH; k++) {
			outImage[i][k] = inImage[inH - k - 1][i];
		}
	}
	printf("\t\t\t < 시계방향 90도 회전 화면 > ");
}
// K.결과 이미지 시계방향으로 180도 회전
void turn180Right() {
	printf("\n\n");
	ori_printScreen();

	for (int i = 0; i < inW; i++) {
		for (int k = 0; k < inH; k++) {
			outImage[i][k] = inImage[inH - i - 1][inW - k - 1];
		}
	}
	printf("\t\t\t < 시계방향 180도 회전 화면 > ");
}
// K.결과 이미지 시계방향으로 270도 회전
void turn270Right() {
	printf("\n\n");
	ori_printScreen();

	for (int i = 0; i < inW; i++) {
		for (int k = 0; k < inH; k++) {
			outImage[i][k] = inImage[k][inH - i - 1];
		}
	}
	printf("\t\t\t < 시계방향 270도 회전 화면 > ");
}
// K.결과 이미지 반시계방향으로 90도 회전
void turn90Left() {
	printf("\n\n");
	ori_printScreen();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[k][inH - 1 - i];
		}
	}
	printf("\t\t\t < 반시계방향 90도 회전 화면 > ");
}
// K.결과 이미지 반시계방향으로 180도 회전
void turn180Left() {
	printf("\n\n");
	ori_printScreen();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[inH - 1 - i][inW - k - 1];
		}
	}
	printf("\t\t\t < 반시계방향 180도 회전 화면 > ");
}
// K.결과 이미지 반시계방향으로 270도 회전
void turn270Left() {
	printf("\n\n");
	ori_printScreen();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[inH - k - 1][i];
		}
	}
	printf("\t\t\t < 반시계방향 270도 회전 화면 > ");
}
// K.자유회전_시계방향 (포워딩)
void turnFree(int val) {
	/* 공식
	xd = cos * xs - sin * ys
	yd = sin * xs + cos * ys
	*/

	double radian = val * 3.141592 / 180.0;
	int xd, yd;
	for (int xs = 0; xs < inH; xs++) {
		for (int ys = 0; ys < inW; ys++) {
			xd = cos(radian) * xs - sin(radian) * ys;
			yd = sin(radian) * xs + cos(radian) * ys;

			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW)) {
				outImage[xd][yd] = inImage[xs][ys];
			}
		}
	}
}
// K.자유회전_시계방향 (백워딩+중앙회전)
void turnFreeCenter(int val) {
	/* 공식
	xs = cos * (xd-cx) + sin * (yd-cy)
	ys = -sin * (xd-cs) + cos * (yd-cy)
	xs += cx;
	ys += cy;
	*/

	double radian = val * 3.141592 / 180.0;
	int cx = outH / 2;
	int cy = outW / 2;
	int xs, ys;
	for (int xd = 0; xd < outH; xd++) {
		for (int yd = 0; yd < outW; yd++) {
			xs = cos(radian) * (xd - cx) + sin(radian) * (yd - cy);
			ys = -sin(radian) * (xd - cx) + cos(radian) * (yd - cy);
			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < inH) && (0 <= ys && ys < inW)) {
				outImage[xd][yd] = inImage[xs][ys];
			}
		}
	}
}
// K.자유회전_반시계방향 (포워딩)
/*
void revTurnFree(int val) {
	// 공식
	// xd = cos * xs - sin * ys
	// yd = sin * xs + cos * ys

	double radian = val * 3.141592 / 180.0;
	int xd, yd;
	for (int xs = 0; xs < inH; xs++) {
		for (int ys = 0; ys < inW; ys++) {
			xd = cos(radian) * xs - sin(radian) * ys;
			yd = sin(radian) * xs + cos(radian) * ys;

			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW)) {
				outImage[xd][yd] = inImage[xs][ys];
			}
		}
	}
}
*/
// K.자유회전_반시계방향 (백워딩+중앙회전)
/*
void revTurnFreeCenter(int val) {
	// 공식
	// xs = cos * (xd-cx) + sin * (yd-cy)
	// ys = -sin * (xd-cs) + cos * (yd-cy)
	// xs += cx;
	// ys += cy;

	double radian = val * 3.141592 / 180.0;
	int cx = outH / 2;
	int cy = outW / 2;
	int xs, ys;
	for (int xd = 0; xd < outH; xd++) {
		for (int yd = 0; yd < outW; yd++) {
			xs = cos(radian) * (xd - cx) + sin(radian) * (yd - cy);
			ys = -sin(radian) * (xd - cx) + cos(radian) * (yd - cy);
			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < inH) && (0 <= ys && ys < inW)) {
				outImage[xd][yd] = inImage[xs][ys];
			}
		}
	}
}
*/

// L.이미지 크기 확대 (포워딩)
void sizeUp(int val) {
	// output의 크기 결정
	outH = inH * val;					// output이 input 과 달라짐
	outW = inW * val;
	outImage = malloc2D(outH, outW);

	//*** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i * val ][k * val] = inImage[i][k];
		}
	}
	printf("\t\t\t < 이미지 확대 (포워딩) 화면 > ");
}
// L.이미지 크기 확대 (백워딩)
void backwardMappingSizeUp(int val) {
	// output의 크기 결정
	outH = inH * val;					// output이 input 과 달라짐
	outW = inW * val;
	outImage = malloc2D(outH, outW);

	//*** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[i / val][k / val];
		}
	}
	printf("\t\t\t < 이미지 확대 (백워딩) 화면 > ");
}
// L.이미지 크기 축소 (포워딩)
void sizeDown(int val) {
	// output의 크기 결정
	outH = inH / val;					// output이 input 과 달라짐
	outW = inW / val;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i / val][k / val] = inImage[i][k];
		}
	}
	printf("\t\t\t < 이미지 축소 (포워딩) 화면 > ");
}
// L.이미지 크기 축소 (백워딩)
void backwardMappingSizeDown(int val) {
	// output의 크기 결정
	outH = inH / val;					// output이 input 과 달라짐
	outW = inW / val;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[i / val][k / val];
		}
	}
	printf("\t\t\t < 이미지 축소 (백워딩) 화면 > ");
}

/*
// L.2배 확대
void doubleUp() {
	imgSize = 1;

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i / 2][k / 2];
		}
	}
}
// L.2배 축소
void doubleDown() {
	imgSize = 2;

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 0;
		}
	}
	for (int i = 0; i < inH / 2; i++) {
		for (int k = 0; k < inW / 2; k++) {
			outImage[i][k] = inImage[i * 2][k * 2];
		}
	}
}
*/
//// ********************************************************************************* ////


