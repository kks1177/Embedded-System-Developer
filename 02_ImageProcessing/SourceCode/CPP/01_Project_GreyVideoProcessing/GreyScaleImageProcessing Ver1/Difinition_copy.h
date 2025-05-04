// Difinition_copy.h


//// *************************** < 메뉴 관련 함수 정의부 > *************************** ////
// 기본 메뉴 UI
void mainMenu() {
	printf("\n");
	printf(" =============================================================================== ");
	printf("\n = \t\t\t\t\t\t\t\t\t       =");
	printf("\n =             ### GreyScale Video Processing Ver 1.0_김기성 ###               =");
	printf("\n = \t\t\t\t\t\t\t\t\t       =");
	printf("\n -------------------------------------------------------------------------------");
	printf("\n\n  [ 파일 메뉴 선택 ] \t 1.열기  2.저장  0.종료 ");
	printf("\n\n  [ 알고리즘 선택 ] \t 1.화소점  2.히스토그램  3.화소영역  4.엣지  5.기하학 \n");
	printf("\n =============================================================================== \n");
	printf(" 선택한 파일명 : % s ", imgName);
}
// 전체 메뉴 UI
void printMenu(char functionChoice) {
	/*if (functionChoice == 0) {
		mainMenu();

		while (1) {
			menuChoice = _getch();
			switch (menuChoice) {
			case '1': pix = 1;	openImage();	break;
			case '2': pix = 2;	saveImage(); break;
			case '0': free2D(inImage, inH); free2D(outImage, outH); break;
			default:
				printf(" 메뉴 잘못 선택! \n");
				Sleep(1000);		 system("cls");
				mainMenu();
			}
			if (pix != 0) break;
		}
		Sleep(2000);		system("cls");
	}*/

	while (1) {
		printf("\n");
		printf(" =============================================================================== ");
		printf("\n = \t\t\t\t\t\t\t\t\t       =");
		printf("\n =             ### GreyScale Video Processing Ver 1.0_김기성 ###               =");
		printf("\n = \t\t\t\t\t\t\t\t\t       =");
		printf("\n -------------------------------------------------------------------------------");
		printf("\n\n  [ 파일 메뉴 선택 ] \t 1.열기  2.저장  0.종료 ");
		printf("\n\n  [ 알고리즘 선택 ] \t 1.화소점  2.히스토그램  3.화소영역  4.엣지  5.기하학 \n");

		// 화소점 처리
		if (functionChoice == 1) {
			algoPick = 1;
			puts("\n\n     [ 1.화소점 처리 기능 선택 ] ");
			puts("\t A.밝기  B.선명도  C.반전  D.흑백  E.비트연산  F.감마변환 ");
			puts("\t G.범위강조  H.파라볼라 변환  I.명암대비 스트래칭 ");
		}
		// 히스토그램 (화소점) 처리
		else if (functionChoice == 2) {
			algoPick = 2;
			puts("\n\n     [ 2.히스토그램 처리 기능 선택 ] ");
			puts("\t A.히스토그램 출력  B.스트래칭  C.엔드-인 탐색  D.평활화 ");
		}
		// 화소영역 처리
		else if (functionChoice == 3) {
			algoPick = 3;
			puts("\n\n     [ 3.화소영역 처리 기능 선택 ] ");
			puts("\t A.엠보싱  B.블러링  C.샤프닝  D.스무딩  ");
		}
		// 화소영역 (엣지) 처리
		else if (functionChoice == 4) {
			algoPick = 4;
			puts("\n\n     [ 4.화소영역 (엣지 검출) 처리 기능 선택 ] ");
			puts("\t A.엣지 검출  ");
		}
		// 기하학 처리
		else if (functionChoice == 5) {
			algoPick = 5;
			puts("\n\n     [ 5.기하학 처리 기능 선택 ] ");
			puts("\t A.미러링  B.회전  C.확대/축소  D.이동  E.워핑  ");
		}
		/*switch (functionChoice) {
		case '1':
			pix = 1;
			puts("\n\n   [ 1.화소점 처리 기능 메뉴 선택 ] ");
			puts("      A.밝기  B.선명도  C.반전  D.흑백  E.비트연산  F.감마변환 ");
			puts("      G.범위강조  H.파라볼라 변환  I.명암대비 스트래칭 ");
			break;
		case '2':
			pix = 2;
			puts("\n\n   [ 2.히스토그램 처리 기능 메뉴 선택 ] ");
			puts("      A.스트래칭  B.엔드-인 탐색  C.평활화 ");
			break;
		case '3':
			pix = 3;
			puts("\n\n   [ 3.화소영역 처리 기능 메뉴 선택 ] ");
			puts("      A.엠보싱  B.블러링  S., , , T., , , U., , , ");
			break;
		case '4':
			pix = 4;
			puts("\n\n   [ 4.기하학 처리 기능 메뉴 선택 ] ");
			puts("      A.미러링  B.회전  C.확대/축소  D.이동 ");
			break;
		default:
			printf("기능 출력 잘못 입력! \n");
			Sleep(1000);		 system("cls");
			mainMenu();
		}*/
		printf("\n =============================================================================== \n");
		printf(" 선택한 파일명 : % s ", imgName);
		if (algoPick != 0) break;
	}

}
// 메뉴 선택
int choiceMenu() {
	char menuChoice = 0;
	char algorithmChoice = 0;
	char menuPick = 0;
	//char algoPick = 0; 
	//char funcPick = 0;

	mainMenu();

	while (1) {
		printf("\t\t 파일 메뉴 선택 : ");
		menuChoice = _getch();
		switch (menuChoice) {
		case '1': menuPick = 1;		openImage();	break;
		case '2': menuPick = 2;		saveImage(); break;
		case '0': free2D(inImage, inH); free2D(outImage, outH); break;
		default:
			puts(" 파일 메뉴 선택 오류!!! \n");
			Sleep(500);		 system("cls");		mainMenu();
		}
		if (menuPick != 0)		break;
	}
	Sleep(2000);		system("cls");	 mainMenu();


	while (1) {
		printf("\t\t 알고리즘 선택 : ");
		algorithmChoice = _getch();
		system("cls");
		inImgCheck();

		switch (algorithmChoice) {
		case '1':	printMenu(1);	break;
		case '2':	printMenu(2);	break;
		case '3':	printMenu(3);	break;
		case '4':	printMenu(4);	break;
		case '5':	printMenu(5);	break;
		default:
			puts(" 알고리즘 선택 오류!!! \n");
			Sleep(500);		system("cls");	 mainMenu();
		}
		//if (algoPick != 0)	break;


		printf("\t\t 기능 선택 : ");
		inKey = _getch();

		// 화소점 처리
		if (algoPick == 1) {
			switch (inKey) {
			case '1': system("cls");		mainMenu();		printf("\t\t 파일 메뉴 선택 : ");	openImage();	break;
			case '2': saveImage(); break;
			case '0': free2D(inImage, inH); free2D(outImage, outH); return 0;

			case 'A':	case 'a':	// 밝기 조절
				brightControlImage();	break;
			case 'B':	case 'b':	// 선명도 조절
				clearControlImage();	break;
			case 'C':	case 'c':	// 반전 조절
				reverseImage();	break;
			case 'D':	case 'd':	// 흑백 (128/평균)
				grayScaleImage();	break;
			case 'E':	case 'e':	// 비트 연산 (And/Or/Xor/Not)
				bitCalcImage();	break;
			case 'F':	case 'f':	// 감마 변환
				gammaConverseImage();	break;
			case 'G':	case 'g':	// 범위 강조 
				rangeEmphasisImage();	break;
			case 'H':	case 'h':	// 파라볼라 변환 
				parabolaImage();	break;
			case 'I':	case 'i':		// 명암대비 스트래칭
				stretchedImage();	break;

			default:
				if (inKey != 'x' && inKey != 'X')		printf(" 화소점 처리 기능 선택 오류!!! \n"); break;
			}
			Sleep(2000);		system("cls");	printMenu(1);
		}

		// 히스토그램 (화소점) 처리
		else if (algoPick == 2) {
			switch (inKey) {
			case '1': system("cls");		mainMenu();		openImage();	break;
			case '2': saveImage(); break;
			case '0': free2D(inImage, inH); free2D(outImage, outH); return 0;

			case 'A':	case 'a':		// 히스토그램 출력
				printHisto();				break;
			case 'B':	case 'b':		// 히스토그램 스트래칭
				histoStretchImage();	break;
			case 'C':	case 'c':		// 히스토그램 엔드-인 탐색
				histoEndInImage();	break;
			case 'D':	case 'd':		// 히스토그램 평활화
				histoEqualImage();	break;

			default:
				if (inKey != 'x' && inKey != 'X')		printf(" 히스토그램 처리 기능 선택 오류!!! \n"); break;
			}
			Sleep(2000);		system("cls");	printMenu(2);
		}

		// 화소영역 처리
		else if (algoPick == 3) {
			switch (inKey) {
			case '1': system("cls");		mainMenu();		openImage();	break;
			case '2': saveImage(); break;
			case '0': free2D(inImage, inH); free2D(outImage, outH); return 0;

			case 'A':	case 'a':	// 엠보싱
				embossingImage();	break;
			case 'B':	case 'b':	// 블러링
				blurringImage();	break;
			case 'C':	case 'c':	// 샤프닝
				sharpeningImage();	break;
			case 'D':	case 'd':	// 스무딩 (가우시안)
				smoothingImage();	break;

			default:
				if (inKey != 'x' && inKey != 'X')		printf(" 화소영역 처리 기능 선택 오류!!! \n"); break;
			}
			Sleep(2000);		system("cls");	printMenu(3);
		}

		// 화소영역 (엣지) 처리
		else if (algoPick == 4) {
			switch (inKey) {
			case '1': system("cls");		mainMenu();		openImage();	break;
			case '2': saveImage(); break;
			case '0': free2D(inImage, inH); free2D(outImage, outH); return 0;

			case 'A':	case 'a':	// 이동과 차분 엣지 검출 (수직, 수평, 수직수평)
				shiftDifferEdgeImage();		break;

			default:
				if (inKey != 'x' && inKey != 'X')		printf(" 기하학 처리 기능 선택 오류!!! \n"); break;
			}
			Sleep(2000);		system("cls");	printMenu(4);
		}

		// 기하학 처리
		else if (algoPick == 5) {
			switch (inKey) {
			case '1': system("cls");		mainMenu();		openImage();	break;
			case '2': saveImage(); break;
			case '0': free2D(inImage, inH); free2D(outImage, outH); return 0;

			case 'A':	case 'a':	// 미러링 (좌우/상하/좌우+상하)
				mirroringImage();		break;
			case 'B':	case 'b':	// 회전 (방향, 90/180/270도/자유)
				turnImage();		break;
			case 'C':	case 'c':	// 이미지 크기(규격) 확대/축소
				imageSizeUpDown();	break;
			case 'D':	case 'd':	// 이미지 이동
				moveImage();	break;
			case 'E':	case 'e':	// 워핑
				warpingImage();	break;

			default:
				if (inKey != 'x' && inKey != 'X')		printf(" 기하학 처리 기능 선택 오류!!! \n"); break;
			}
			Sleep(2000);		system("cls");	printMenu(5);
		}
	}
	system("cls");
	printf(" 종료되었습니다.\n");
	free2D(inImage, inH); free2D(outImage, outH);
	return 0;
}

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

	printf("\n\n\n     파일명 --> ");	// cat01, dog13
	scanf("%s", imgName);

	while (1) {
		printf("\n\t [픽셀 선택] \n");
		printf("\n\t   1.128  2.256  3.512 ");

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
			printf("\n\n\t 입력 오류! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			mainMenu();	printf("     파일명 --> ");
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

	puts("");
	ori_printScreen();
}
// 2.출력 이미지 저장 함수
void saveImage() {
	char fullName[100] = "C:/images/Gallery/Gallery";			// C:/images/Pet_RAW(squre)/Pet_RAW(512x512)/";

	printf("\n\n\n     (저장) 파일명 --> ");	// cat01, dog13
	scanf("%s", imgName);

	while (1) {
		printf("\n\t [(저장) 픽셀 선택] \n");
		printf("\n\t   1.128  2.256  3.512  0.저장 취소 ");

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
			printf("\n\n\t 저장 실패! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			mainMenu();	printf("     (저장) 파일명 --> ");
			break;
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

	puts("");
	ori_printScreen();
}
// 모핑할 이미지 open (입력)
/*
void openMorpImage() {
	char fullName[100] = "C:/images/Gallery/Gallery";			// C:/images/Pet_RAW(squre)/Pet_RAW(512x512)/";

	printf("\n\n     파일명 --> ");	// cat01, dog13
	scanf("%s", imgName);

	while (1) {
		printf("\n\t [픽셀 선택] \n");
		printf("\n\t   1.128  2.256  3.512 ");

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
			printf("\n\n\t 입력 오류! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			mainMenu();	printf("     파일명 --> ");
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
	morpImage = malloc2D(inH, inW);

	// 파일 --> 메모리로 로딩
	rfp = fopen(filePath, "rb");
	for (int i = 0; i < inH; i++) {
		fread(morpImage[i], sizeof(unsigned char), inW, rfp);
	}

	//// 파일 닫기 ////
	fclose(rfp);

	puts("\n");
	ori_printScreen();
}
*/

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
	if (oriImage == 1)
		outImg_128();
	//else if (oriImage == 9)
	//	morpOutImg();

	// 결과 이미지를 각각 다른 위치에 띄우고 싶을 때 사용
	/*
	// Result 128x128
	if (oriImage == 1)
		outImg_128();
	// Result 256x256
	else if (oriImage == 2)
		outImg_256();
	// Result 512x512
	else if (oriImage == 3)
		outImg_512();
	*/
}
// 원본 이미지 화면 출력
void ori_printScreen() {
	if (pix == 1)	originImage(1);				// 128x128
	else if (pix == 2)	originImage(2);		// 256x256
	else if (pix == 3)	originImage(3);		// 512x512
}
// 결과 이미지 화면 출력
void res_printScreen() {
	if (pix == 1 || pix == 2 || pix == 3)
		resultImage(1);
	//else if (morpPix == 1)
	//	resultImage(9);

	// 결과 이미지를 각각 다른 위치에 띄우고 싶을 때 사용
	/*
	if (pix == 1)	resultImage(1);				// 128x128
	else if (pix == 2)	resultImage(2);		// 256x256
	else if (pix == 3)	resultImage(3);		// 512x512
	*/
}
//// ********************************************************************************* ////



//// ************************* < 1.화소점 처리 기능 함수 정의부 > ********************** ////
// 1-A.이미지 밝기 값 조절
void brightControlImage() {
	// *******함수마다 붙이기******** //
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);
	// ****************************** // 

	inImgCheck();

	int value;

	printf("\n\n\t 밝기 조절 값 --> ");
	scanf_s("%d", &value);

	ori_printScreen();
	// **************** 알고리즘 부분 *****************  //
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
		printf("\t\t\t\t\t  < 밝기 %d 증가 화면 >", value);
	else if (value < 0)
		printf("\t\t\t\t\t  < 밝기 %d 감소 화면 >", value);
	else
		printf("\n\n 다시 입력하세요! \n");
	res_printScreen();
}

// 1-B.이미지 선명도 조절
void clearControlImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();
	// **************** 알고리즘 부분 *****************  
	int value = 0;

	printf("\n\n\t [선명도 조절] ");
	printf("\n\t   1.선명하게  2.희미하게 ");

	inKey = _getch();
	if (inKey == '1') {
		printf("\t   선명도 조절 값(양수) --> ");
		scanf_s("%d", &value);

		while (1) {
			if (value > 0)		break;
			else
				printf("\n\t 입력오류! 양수를 다시 입력하세요! \n");
		}
	}
	else if (inKey == '2') {
		printf("\t   선명도 조절 값(양수) --> ");
		scanf_s("%d", &value);

		while (1) {
			if (value > 0)		break;
			else
				printf("\n\t입력오류! 양수를 다시 입력하세요! \n");
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
		mainMenu();	printf("\t\t 파일명 --> ");
		break;
	}
}

// 1-C.이미지 반전 처리
void reverseImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	puts("\n\n");
	ori_printScreen();
	// **************** 알고리즘 부분 *****************  
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[i][k];

			outImage[i][k] = 255 - px;
		}
	}
	printf("\t\t\t\t\t  < 영상 반전 화면 > ");
	res_printScreen();
}

// 1-D.이미지 흑백 처리
void grayScaleImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	printf("\n\n\t\t  1.128 기준  2.평균값 기준 \n");

	ori_printScreen();
	// **************** 알고리즘 부분 *****************  
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

// 1-E.비트연산 (And/Or/Xor/Not)
void bitCalcImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();
	// **************** 알고리즘 부분 *****************  
	int value = 0;

	printf("\n\n\t\t 1.And  2.Or  3.Xor  4.Not ");

	inKey = _getch();
	if (inKey == '1' || inKey == '2' || inKey == '3') {
		while (1) {
			printf("\t 연산할 값 (0 or 255) : ");
			scanf_s("%d", &value);

			if (0 <= value && value <= 255)
				break;
			else
				printf("\n\t 입력오류! 값(0~255)을 다시 입력하세요! \n");
		}
	}
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

// 1-F.감마 변환
// 감마 : 빛의 변화를 비선형적으로 변화시킨 것
void gammaConverseImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	// 출력 변수 설정
	outH = inH;
	outW = inW;
	// 출력 이미지 동적 할당
	outImage = malloc2D(outH, outW);

	inImgCheck();
	// **************** 알고리즘 부분 ***************** 
	float value = 0;

	printf("\n\n\t 감마 값 입력 : ");
	scanf_s("%f", &value);

	ori_printScreen();

	if (value != 0)
		for (int i = 0; i < inH; i++)
			for (int k = 0; k < inW; k++) {
				float gamma = pow(float(inImage[i][k]), 1 / value);
				if (gamma > 255)
					outImage[i][k] = 255;
				else if (gamma < 0)
					outImage[i][k] = 0;
				else
					outImage[i][k] = gamma;
			}
	else
		printf(" 다시 입력하세요! \n");
	printf("\t\t\t\t\t  < 감마 변환(%.1f) 화면 > ", value);
	res_printScreen();
}

// 1-G.범위 강조
void rangeEmphasisImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();
	// **************** 알고리즘 부분 *****************  //
	int start = 0;
	int end = 0;

	printf("\n\t 범위 강조 초기값 : ");
	scanf("%d", &start);
	printf("\t 범위 강조 종료값 : ");
	scanf("%d", &end);

	ori_printScreen();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if ((start <= inImage[i][k]) && (inImage[i][k] < end))
				outImage[i][k] = 255;
			else
				outImage[i][k] = inImage[i][k];
		}
	}
	printf("\t\t\t\t\t  < 범위 강조 화면 (범위 : %d ~ %d) > ", start, end);
	res_printScreen();
}

// 1-H.파라볼라 변환
// (CAP : 밝은 곳이 입체적으로 보임, CUP : 어두운 곳이 입체적)
void parabolaImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	printf("\n\n\t\t 1.파라볼라(CAP)  2.파라볼라(CUP) \n");

	ori_printScreen();
	// **************** 알고리즘 부분 *****************  //
	inKey = _getch();
	switch (inKey) {
	case '1':
		parabolaCap();
		break;
	case '2':
		parabolaCup();
		break;
	default:
		printf("\t\t 다시 입력하세요! \n");
		break;
	}
	res_printScreen();
}

// 1-I.명암대비 스트래칭
void stretchedImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();
	// **************** 알고리즘 부분 ***************** 
	float value = 0;
	printf("\n\n\t\t 스트레칭 조절 값 : ");
	scanf("%f", &value);

	ori_printScreen();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			float px = inImage[i][k] + (outImage[i][k] - 128) * value;
			if (px > 255)
				outImage[i][k] = 255;
			else if (px < 0)
				outImage[i][k] = 0;
			else
				outImage[i][k] = (unsigned char)px;
		}
	}
	printf("\t\t\t\t\t  < 스트래칭 화면 > ");
	res_printScreen();
}
//// ********************************************************************************* ////


//// ************************ < 2.화소점(히스토그램) 처리 기능 함수 정의부 > ************************ ////
// 2-A.히스토그램 출력
void printHisto() {
	// 기존 출력 메모리 해제
	free2D(outImage, outH);
	outH = 256;
	outW = 256;
	int reSize = outH * outW;

	puts("\n\n\n");
	ori_printScreen();

	unsigned char hist[256] = { 0 };		// 히스토그램 행렬
	int LOW = 0;
	int HIGH = 255;
	unsigned char value = 0;

	//초기화
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	//빈도수 조사
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			value = inImage[i][k];
			hist[value]++;
		}
	}

	// 정규화
	unsigned char min = 0;// 최소값 초기화
	unsigned char max = 0; // 최대값 초기화
	unsigned char dif;
	int hNum = 0;
	for (int i = 0; i < 256; i++) {
		if (hist[i] <= min) min = (unsigned char)hist[i];
		if (hist[i] >= max) max = (unsigned char)hist[i];
	}
	dif = max - min;
	unsigned char scaleHist[256] = { 0 };

	// 정규화 된 히스토그램
	for (int i = 0; i < 256; i++) {
		scaleHist[i] = (unsigned char)((hist[i] - min) * HIGH / dif);
	}

	// 정규화된 히스토그램 출력
	unsigned char* OutImage = (unsigned char*)malloc((reSize) * sizeof(unsigned char));

	// 정규화된히스토그램의값은출력배열에검은점(0)으로표현
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < scaleHist[i]; k++) {
			OutImage[outW * (outH - k - 1) + i] = 0;
		}
	}
	hNum = 0;
	outImage = malloc2D(outH, outW);
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = OutImage[hNum];
			hNum++;
		}
	}
	free(OutImage);
	res_printScreen();
}

// 2-B.히스토그램 스트래칭
void histoStretchImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	puts("\n\n\n");
	ori_printScreen();
	// **************** 알고리즘 부분 ***************** 
	/* 공식.
	 out = (in - low) / (high - low) * 255.0;.*/

	int low = inImage[0][0], high = inImage[0][0];		// 초기화 가장 안전한 방법
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			outImage[i][k] = (double)(inImage[i][k] - low) / (high - low) * 255.0;

	printf("\t\t\t\t\t  < 이미지 히스토그램 스트래칭 화면 > ");
	res_printScreen();
}

// 2-C.히스토그램 엔드-인 탐색
void histoEndInImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	puts("\n\n\n");
	ori_printScreen();
	// **************** 알고리즘 부분 ***************** 
	int low = inImage[0][0], high = inImage[0][0];		// 초기화 가장 안전한 방법
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}
	low += 50;
	high -= 50;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			double res = (double)(inImage[i][k] - low) / (high - low) * 255.0;
			if (res <= 0.0)
				outImage[i][k] = 0;
			else if (res > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = res;
		}
	}
	printf("\t\t\t\t\t  < 이미지 히스토그램 엔드-인 탐색 화면 > ");
	res_printScreen();
}

// 2-D.히스토그램 평활화
/*
* 1단계 : 명암 값 j의 빈도수 hist[j]를 계산해 입력 영상이 히스토그램 생성
* 2단계 : 각 명암 값 i에서 0~i까지의 누적 빈도수(누적합)를 계산
* 3단계 : 2단계에서 구한 누적 빈도수를 정규화 (정규화 누적합)
*/
void histoEqualImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	puts("\n\n\n");
	ori_printScreen();

	// **************** 알고리즘 부분 ***************** 
	// 1단계 : 히스토그램 생성
	int histo[256] = { 0, };
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			histo[inImage[i][k]]++;

	// 2단계 : 누적 히스토그램 생성 (누적합 생성)
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];

	// 3 단계 : 정규화된 누적 히스토그램 생성 (정규화된 누적합 생성)
	// n = sum * (1/(inH*inW)) * 255.0
	double normalHisto[256] = { 0, };
	for (int i = 0; i < 256; i++)
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;

	// 4단계 : 원래값을 정규화 값으로 치환
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			outImage[i][k] = normalHisto[inImage[i][k]];

	printf("\t\t\t\t\t  < 이미지 히스토그램 평활화 화면 > ");
	res_printScreen();
}
//// ******************************************************************************* ////


//// ************************** < 3.화소 영역 처리 기능 함수 정의부 > ************************** ////
double** malloc2D_double(int row, int col) {
	double** retMemory;
	retMemory = (double**)malloc(row * sizeof(double*));
	for (int i = 0; i < row; i++)
		retMemory[i] = (double*)malloc(col * sizeof(double));
	return retMemory;
}
void free2D_double(double** memory, int h) {
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
}

// 3-A.엠보싱 처리
// 입력 영상을 양각 형태로 보이게 하는 기술
void embossingImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	puts("\n\n\n");
	ori_printScreen();
	// **************** 알고리즘 부분 ***************** 
	const int MSIZE = 3;
	// 엠보싱 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ { -1,  0,  0},
	  {  0,  0,  0},
	  {  0,  0,  1} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];
			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크 합계가 0일 경우에만 추가 
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}
	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut, outH);
	//*****************************
	printf("\t\t\t\t\t  < 엠보싱 처리 화면 > ");
	res_printScreen();
}

// 3-B.블러링 처리 (3x3, 5x5)
// 영상을 흐리게 하거나 부드럽게 하는 기술
// 저주파(Low Pass Filter) 통과, 고주파(High Pass Filter) 제거  --> 인덕터
void blurringImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	printf("\n\n\t 1.3x3  2.5x5 ");

	puts("\n\n");
	ori_printScreen();
	// **************** 알고리즘 부분 ***************** 
	inKey = _getch();

	switch (inKey) {
	case '1':	blurring33();		break;
	case '2':	blurring55();		break;
	default:
		printf("\n\n\t 다시 입력하세요!!! \n");
	}
	res_printScreen();
}

// 3-C.샤프닝 처리 (샤프닝, 고주파필터 처리 샤프닝, 저주파필터 처리 샤프닝)
// 블러링 반대, 상세한 부분 더욱 강조
// 고주파(High Pass Filter) 통과, 저주파(Low Pass Filter) 제거  --> 커패시터
void sharpeningImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	printf("\n\n\t 1.샤프닝  2.HPF샤프닝  3.LPF샤프닝 ");

	puts("\n\n");
	ori_printScreen();
	// **************** 알고리즘 부분 ***************** 
	inKey = _getch();

	switch (inKey) {
	case '1':	sharpening();	break;
	case '2':	HPF_sharp();	break;
	case '3':	LPF_sharp();		break;
	}
	res_printScreen();
}

// 3-D.스무딩(가우시안) 처리
// 세세한 부분을 제거하여 부드럽게 함
void smoothingImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	puts("\n\n\n");
	ori_printScreen();
	// **************** 알고리즘 부분 ***************** 
	const int MSIZE = 3;
	// 스무딩 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  1. / 16,  1. / 8,  1. / 16},
	  {   1. / 8,   1. / 4,   1. / 8},
	  {  1. / 16,  1. / 8,  1. / 16} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];
			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut[i][k] += 127.0;
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}

	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut, outH);
	//*****************************
	printf("\t\t\t\t\t  < 스무딩(가우시안) 처리 화면 > ");
	res_printScreen();
}
//// ********************************************************************************* ////


//// ************************** < 4.화소 영역 (엣지 검출) 처리 기능 함수 정의부 > ************************** ////
// 4-A.이동과 차분 엣지 검출 (수직, 수평, 수직수평)
// 화소의 위치를 위/아래/왼/오른쪽으로 하나씩 이동 -> 원래 화소 값 - 이동위치 화소 값
// 엣지 검출기는 대부분 이 방법 응용
// Shift & Difference
void shiftDifferEdgeImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	printf("\n\n\t 1.수직  2.수평  3.수직*수평 ");

	puts("\n");
	ori_printScreen();
	// **************** 알고리즘 부분 ***************** 
	inKey = _getch();

	switch (inKey) {
	case '1':	horizontalEdge();			break;
	case '2':	verticalEdge();		break;
	case '3':	horiVertiEdge();	break;
	}
	res_printScreen();
}
//// ********************************************************************************* ////


//// ************************** < 5.기하학 처리 기능 함수 정의부 > ************************** ////
// 5-A.미러링 (좌우/상하/좌우+상하) 
void mirroringImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	printf("\n\n\t 1.좌우  2.상하  3.상하+좌우 ");

	puts("");
	ori_printScreen();
	// **************** 알고리즘 부분 ***************** 
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
		printf(" 다시 입력하세요! \n");
		break;
	}
	res_printScreen();
}

// 5-B.회전(오른쪽,왼쪽 90/180/270/자유-백워딩+중앙)
void turnImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();
	// **************** 알고리즘 부분 ***************** 
	int direct = 0;

	printf("\n\n\t [방향] 1.오른쪽  2.왼쪽  3.자유 ");
	scanf_s("%d", &direct);

	// 시계방향 회전
	if (direct == 1) {
		printf("\n\t\t    [각도_시계방향] 1.90  2.180  3.270 ");
		inKey = _getch();

		ori_printScreen();

		switch (inKey) {
		case '1':	// 90도 회전
			turn90Right();	break;
		case '2':	// 180도 회전
			turn180Right();	break;
		case '3':	// 270도 회전
			turn270Right();	break;
		default:
			break;
		}
	}
	// 반시계방향 회전
	else if (direct == 2) {
		printf("\n\t\t    [각도_반시계방향] 1.90  2.180  3.270 ");
		inKey = _getch();

		ori_printScreen();

		switch (inKey) {
		case '1':	// 90도 회전
			turn90Left();	break;
		case '2':	// 180도 회전 
			turn180Left();	break;
		case '3':	// 270도 회전
			turn270Left();	break;
		default:
			break;
		}
	}
	// 자유회전
	else if (direct == 3) {
		int angle;
		printf("\n\t\t회전 각도 --> ");
		scanf("%d", &angle);

		printf("\t\t 1.자유회전  2.자유회전(백워딩+중앙) ");

		ori_printScreen();

		inKey = _getch();
		switch (inKey) {
		case '1':		// 자유회전
			turnFree(angle);		break;
		case '2':		// 자유회전 (백워딩+중앙)
			turnFreeCenter(angle);		break;
		default:
			printf("\n\t\t 입력 오류! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			mainMenu();	printf("\t\t 파일명 --> ");
		}
	}
	else {
		printf("\t\t다시 입력해주세요! \n");
		return;
	}
	res_printScreen();
}

// 5-C.이미지 크기(규격) 확대/축소
void imageSizeUpDown() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();
	// **************** 알고리즘 부분 ***************** 
	int scale = 0;

	printf("\n\n\t\t 1.이미지 크기 확대 (포워딩)   2.이미지 크기 확대 (백워딩) ");
	printf("\n\n\t\t 3.이미지 크기 축소 (포워딩)   4.이미지 크기 축소 (백워딩) ");

	inKey = _getch();
	if (inKey == '1' || inKey == '2') {
		printf("\t\t 이미지 확대 배율 : ");
		scanf("%d", &scale);

		while (1) {
			if (scale > 0)
				break;
			else
				printf("\n\t\t 입력오류! 양수를 다시 입력하세요! \n");
		}
	}
	else if (inKey == '3' || inKey == '4') {
		printf("\t\t 이미지 축소 배율 : ");
		scanf("%d", &scale);

		while (1) {
			if (scale > 0)
				break;
			else
				printf("\n\t\t 입력오류! 양수를 다시 입력하세요! \n");
		}
	}
	else
		printf("\t\t 다시 입력하세요! \n");

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

// 5-D.이동
void moveImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();
	// **************** 알고리즘 부분 ***************** 
	int value = 0;

	printf("\n\n\t\t  이동할 값 : ");
	scanf("%d", &value);

	puts("\n");
	ori_printScreen();

	// 출력 이미지 0으로 초기화
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			outImage[i][k] = 0;

	for (int i = 0; i < inH - value; i++)
		for (int k = 0; k < inW - value; k++)
			outImage[i][k] = inImage[i + value][k + value];

	printf("\t\t\t\t\t  < %d만큼 이동한 화면 > ", value);
	res_printScreen();
}

// 5-E.워핑
void warpingImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	puts("\n\n\n");
	ori_printScreen();
	// **************** 알고리즘 부분 ***************** 
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			outImage[i][k] = 0;

	for (int k = 0; k < outW; k++) {
		double f_px = (4.0 / outH) * k * (outW - k);
		double b_px = (4.0 / outH) * (k + 1) * (outW - k - 1);
		int px = int((f_px + b_px) / 2);
		double rate = double(outH) / px;

		for (int i = 0; i < px; i++) {
			unsigned long sum = 0;
			for (int l = int(i * rate); l<int((i + 1) * rate); l++)
				sum += inImage[l][k];
			outImage[i][k] = sum / (int((i + 1) * rate) - int(i * rate));
		}
	}
	printf("\t\t\t\t\t  < 워핑된 이미지 > ");
	res_printScreen();
}

// 5-F.모핑
/*
void morphingImage() {
	free2D_out();

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	inImgCheck();

	puts("\n\n");
	ori_printScreen();
	// **************** 알고리즘 부분 *****************
	printf("\n\n 모핑할 이미지 추가 \n");


	printf("\t\t\t\t\t  < 모핑된 이미지 > ");
	res_printScreen();
}
*/

// E.양선형 보간법 회전
// Binary interpolation rotation
//void rotateBinaryInterpol() {// 영상 회전 알고리즘. 중앙회전+백워딩+확대
//
//	// 기존 출력 메모리 해제
//	free2D(m_OutImage, m_outH); // 해제가 위에 오는 이유는 출력 width,height가 입력과 다를 수 있기 때문에 폭넓이 결정전에 해야한다.
//
//
//	// 진짜 영상처리 알고리즘
//
//	int angle; // 0~ 360 인데 컴퓨터는 radian으로 인식 따라서 변환해주어야함
//	printf("이동 각도 크기 입력:\n  ");
//	scanf("%d", &angle);
//
//
//
//	double radian = (angle * 3.141592) / 180.0;
//	double radian90 = ((90 - angle) * 3.141592) / 180.0;  // 90도 넘는 각을 어떻게 계산할지 생각
//	// newX = cos * x - sin * y  영상 회전 공식 x = i , y = k
//	// newY = sin * x + cos * y
//
//
//
//	//(중요!) 출력 영상의 높이와 폭을 결정해야한다 --> 알고리즘에 따라 달라져야함
//
//	m_outH = (int)(m_inH * fabs(cos(radian90)) + m_inW * fabs(cos(radian)));     // 확대를 위해 입력받은 뒤 상 출력 폭 넓이 정해야 해서 위치를 아래로
//	m_outW = (int)(m_inW * fabs(cos(radian)) + m_inW * fabs(cos(radian90)));   // 실수형을 정수로 바꿧다. 실수가 나올 수 있기 때문  
//																				 // cos값이 음수될 수 있기 떄문에 fabs로 실수일때 절대값 취해줌
//	// 출력 영상 메모리 할당
//
//	m_OutImage = malloc2D(m_outH, m_outW);
//
//	// 임시 입력 영상 -----> 출력과 크기가 같게 하고 , 입력 영상에 두기
//
//	UC** tmpInput = malloc2D(m_outH, m_outW); // 임시 입력 영상 메모리 할당 (출력크기로 할당) 
//
//
//	int dx = (m_outW - m_inW) / 2;
//	int dy = (m_outH - m_inH) / 2;
//
//	for (int i = 0; i < m_inH; i++) {
//		for (int k = 0; k < m_inW; k++) {
//
//			tmpInput[i + dy][k + dx] = m_InImage[i][k]; // 원본영상을 tmpInput에 그대로 저장하는데 tmpInput은 (0,0) 좌표에서 중앙으로 이동시킴(dy,dx)
//			m_OutImage[i][k] = 0;
//		}
//	}
//
//
//	// 중앙 위치 구하기
//	int centerx = m_outW / 2; //회전 사진의 중앙
//	int centery = m_outH / 2;
//
//	int x1, x2, y1, y2;
//	double rx, ry, p, q, value;
//
//
//	//for (int i = 0; i < m_outH; i++) { // 백워딩, 역방향 사상 : 출력 기준으로 for문 돌려야함
//	//	for (int k = 0; k < m_outW; k++) {
//
//	//		int oldI = (cos(radian) * (i - centerx) + sin(radian) * (k - centery)) + centery;  // 중앙기준 회전을 위해 만든 공식 , 백워딩기준으로 바꿈 부호도
//	//		int oldK = (-sin(radian) * (i - centerx) + cos(radian) * (k - centery)) + centerx;
//
//	//		if (((0 <= oldI) && (oldI < m_outH)) && ((0 <= oldK) && (oldK < m_outW))) {
//
//
//	//			tmpOutput[i][k] = tmpInput[oldI][oldK] ;   // 중앙에 놓은 tmpInput을 돌려준다. 
//
//
//	//		}
//	//		
//
//
//	//	}
//	//}
//
//	for (int i = 0; i < m_outH; i++) {
//		for (int k = 0; k < m_outW; k++) {
//
//			// 실수형 변수 rx, ry는 입력 영상에서 참조할 픽셀 값의 실수 좌표 
//			rx = (double)(-sin(radian)) * (i - centerx) + cos(radian) * (k - centery) + centerx;
//			ry = (double)(cos(radian)) * (i - centerx) + sin(radian) * (k - centery) + centery;
//
//			if (0 <= rx && rx < m_outW && 0 <= ry && ry < m_outH) {
//				// x1, x2, y1, y2는 각각(rx, ry) 좌표를 둘러싼 4개의 픽셀 좌표를 나타낸다.
//				x1 = (int)rx;
//				y1 = (int)ry;
//
//				x2 = x1 + 1;
//				if (x2 == m_outW) {
//					x2 = m_outW - 1;
//				}
//
//				y2 = y1 + 1;
//				if (y2 == m_outH) {
//					y2 = m_outH - 1;
//				}
//				// p와 q는 0부터 1 사이의 값을 갖는 실수형 변수 
//				p = rx - x1;
//				q = ry - y1;
//
//				value = (1. - p) * (1. - q) * tmpInput[y1][x1]
//					+ p * (1. - q) * tmpInput[y2][x1]
//					+ (1. - p) * q * tmpInput[y1][x2]
//					+ p * q * tmpInput[y2][x2];
//
//
//				if (value > 255) {
//					value = 255;
//				}
//				else if (value < 0) {
//					value = 0;
//				}
//				m_OutImage[i][k] = (UC)value;
//			}
//
//		}
//	}
//
//	free2D(tmpInput, m_outH); // 임시 입력 영상 메모리 해줘야 RAM 누수 안일어남
//	displayImage();
//
//}

// F.양선형 보간법 확대
// Enlarging bimodal interpolation.
//void enlargeBinaryInterpol() {
//
//}

//// ******************************************************************************* ////




//// *************************** < 결과 처리 함수 정의부 > *************************** ////
// 입력 이미지 입력 여부 확인
void inImgCheck() {
	if (inImage == NULL) {
		printf("\n\n  < 주의!!! > 입력 이미지 없음!! 이미지를 먼저 불러오세요! \n");
		Sleep(1500);
		system("cls");
		mainMenu();
		//return;
	}
}

// 이미지 파일 입력_128x128
void inImg_128() {
	short px = 0;
	printf("\n\n     < 원본 이미지 화면(128) > ");
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			px = inImage[i][k];
			SetPixel(hdc, k + 50, i + 470, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 입력_256x256
void inImg_256() {
	short px = 0;
	printf("\n\n     < 원본 이미지 화면(256) > ");
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			px = inImage[i][k];
			SetPixel(hdc, k + 50, i + 470, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 입력_512x512
void inImg_512() {
	short px = 0;
	printf("\n\n     < 원본 이미지 화면(512) > ");
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			px = inImage[i][k];
			SetPixel(hdc, k + 50, i + 470, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 출력_128x128
void outImg_128() {
	short px = 0;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			px = outImage[i][k];
			SetPixel(hdc, k + 600, i + 470, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 출력_256x256
void outImg_256() {
	short px = 0;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			px = outImage[i][k];
			SetPixel(hdc, k + 600, i + 470, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 이미지 파일 출력_512x512
void outImg_512() {
	short px = 0;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			px = outImage[i][k];
			SetPixel(hdc, k + 600, i + 470, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
// 모핑할 이미지 출력
/*
void morpOutImg() {
	short px = 0;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			px = outImage[i][k];
			SetPixel(hdc, k + 1000, i + 200, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
		}
	}
}
*/


// 1-B.선명하게
void clearUp(int val) {
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
		printf("\t\t\t\t\t  < 선명도 %d 증가 화면 >", val);
		res_printScreen();
	}
	else
		printf("\t\t음수 또는 0 입력.. 양수를 입력해주세요.");
}
// 1-B.흐릿하게
void clearDown(int val) {
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
		printf("\t\t\t\t\t  < 선명도 %d 감소 화면 >", val);
		res_printScreen();
	}
	else
		printf("\t\t음수 또는 0 입력.. 양수를 입력해주세요.");
}

// 1-D.흑백처리 (128 기준)
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
	printf("\t\t\t\t\t  < 영상 흑백 처리(128 기준) 화면 > ");
	res_printScreen();
}
// 1-D.흑백처리 (평균값 기준)
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
	printf("\t\t\t\t\t  < 영상 흑백 처리(평균값 %d 기준) 화면 > ", pixelAvg);
	res_printScreen();
}

// 1-E.비트연산_And
void bitCalc_And(int val) {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			unsigned char px = inImage[i][k] & val;

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t\t\t  < AND 비트 연산 화면, 입력값 : %d > ", val);
	res_printScreen();
}
// 1-E.비트연산_Or
void bitCalc_Or(int val) {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			unsigned char px = inImage[i][k] | val;

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t\t\t  < OR 비트 연산 화면, 입력값 : %d > ", val);
	res_printScreen();
}
// 1-E.비트연산_Xor
void bitCalc_Xor(int val) {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			unsigned char px = inImage[i][k] ^ val;

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t\t\t  < XOR 비트 연산 화면, 입력값 : %d > ", val);
	res_printScreen();
}
// 1-E.비트연산_Not
void bitCalc_Not() {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			unsigned char px = ~inImage[i][k];

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t\t\t  < NOT 비트 연산 화면 > ");
	res_printScreen();
}

// 1-H.파라볼라_CAP 변환
void parabolaCap() {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			float px = (4 / 255.0) * inImage[i][k] * (255 - inImage[i][k]);
			outImage[i][k] = (unsigned char)px;
		}
	}
	printf("\t\t\t\t\t  < 파라볼라_CAP 변환 화면 > ");
}
// 1-H.파라볼라_CUP 변환
void parabolaCup() {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			float px = (4 / 255.0) * inImage[i][k] * (inImage[i][k] - 255) + 255;
			outImage[i][k] = (unsigned char)px;
		}
	}
	printf("\t\t\t\t\t  < 파라볼라_CUP 변환 화면 > ");
}


// 3-B.3x3 블러링
void blurring33() {
	const int MSIZE = 3;
	// 3x3 블러링 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  1. / 9,  1. / 9,  1. / 9  },
	  {  1. / 9,  1. / 9,  1. / 9  },
	  {  1. / 9,  1. / 9,  1. / 9  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut[i][k] += 127.0;
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}

	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut, outH);
	//*****************************
	printf("\t\t\t\t\t  < 3x3 블러링 처리 화면 > ");
}
// 3-B.5x5 블러링
void blurring55() {
	const int MSIZE = 5;
	// 5x5 블러링 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
	  {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
	  {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
	  {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
	  {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 4, inW + 4);		// 엣지구간 마스킹을 간단하게 하기위해. (넓어진 영역들은 삭제될 예정)
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 2][k + 2] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut[i][k] += 127.0;
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}

	free2D_double(tmpIn, inH + 4);
	free2D_double(tmpOut, outH);
	//*****************************
	printf("\t\t\t\t\t  < 5x5 블러링 처리 화면 > ");
}

// 3-C.샤프닝
void sharpening() {
	const int MSIZE = 3;
	// 샤프닝 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ { -1, -1, -1},
	  { -1,  9, -1},
	  { -1, -1, -1} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut[i][k] += 127.0;
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}

	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut, outH);
	//*****************************
	printf("\t\t\t\t\t  < 샤프닝 처리 화면 > ");
}
// 3-C.고주파필터 처리 샤프닝
void HPF_sharp() {
	const int MSIZE = 3;
	// 고주파필터 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  -1. / 9,  -1. / 9,  -1. / 9  },
	  {  -1. / 9,   8. / 9,  -1. / 9  },
	  {  -1. / 9,  -1. / 9,  -1. / 9  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}

	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut, outH);
	//*****************************
	printf("\t\t\t\t\t  < 고주파필터 처리 샤프닝 화면 > ");
}
// 3-C.저주파필터 처리 샤프닝
void LPF_sharp() {
	const int MSIZE = 3;
	// 저주파 필터 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {	1. / 16,	2. / 16,	1. / 16},
	  {	2. / 16,	4. / 16,	2. / 16},
	  {	1. / 16,	2. / 16,	1. / 16} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}

	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut, outH);
	//*****************************
	printf("\t\t\t\t\t  < 저주파필터 처리 샤프닝 화면 > ");
}


// 4-A.수직 엣지
void horizontalEdge() {
	const int MSIZE = 3;
	// 수직 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double Hmask[MSIZE][MSIZE] =
	{ {0,0,0},
	  {-1,1,0},
	  {0,0,0} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * Hmask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}

	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut, outH);
	//*****************************
	printf("\t\t\t\t\t  < 수직 엣지 처리 화면 > ");
}
// 4-A.수평 엣지
void verticalEdge() {
	const int MSIZE = 3;
	// 수평 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double Vmask[MSIZE][MSIZE] =
	{ {0,-1,0},
	  {0,1,0},
	  {0,0,0} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * Vmask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}

	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut, outH);
	//*****************************
	printf("\t\t\t\t\t  < 수평 엣지 처리 화면 > ");
}
// 4-A.수직수평 엣지
void horiVertiEdge() {
	const int MSIZE = 3;
	// 수직 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double Hmask[MSIZE][MSIZE] =
	{ {0,0,0},
	  {-1,1,0},
	  {0,0,0} };
	// 수평 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double Vmask[MSIZE][MSIZE] =
	{ {0,-1,0},
	  {0,1,0},
	  {0,0,0} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut1, ** tmpOut2;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut1 = malloc2D_double(outH, outW);
	tmpOut2 = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S1; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S1 = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S1 += tmpIn[i + m][k + n] * Hmask[m][n];

			tmpOut1[i][k] = S1;
		}
	}
	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S2; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S2 = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S2 += tmpIn[i + m][k + n] * Vmask[m][n];

			tmpOut2[i][k] = S2;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOut1[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++) {
			double v1 = tmpOut1[i][k];
			double v2 = tmpOut2[i][k];
			double v = v1 + v2;
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;

			outImage[i][k] = v;
		}

	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut1, outH);
	free2D_double(tmpOut2, outH);
	//*****************************
	printf("\t\t\t\t\t  < 수직/수평 엣지 처리 화면 > ");
}


// 5-A.이미지 좌우 미러링
void L_R_mirroring() {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[i][inW - 1 - k];		// (최대열 - 1) - 반복자

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t\t\t  < 영상 좌우 미러링 화면 > ");
}
// 5-A.이미지 상하 미러링
void T_B_mirroring() {
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[inH - 1 - i][k];		// (최대행 - 1) - 반복자

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t\t\t  < 영상 상하 미러링 화면 > ");
}
// 5-A.이미지 상하+좌우 미러링
void TB_LR_mirroring() {
	for (int i = 0; i < inW; i++) {
		for (int k = 0; k < inH; k++) {
			int mirror_i = inH - 1 - i;
			int mirror_k = inW - 1 - k;

			outImage[i][k] = inImage[mirror_i][mirror_k];
		}
	}
	printf("\t\t\t\t\t  < 영상 상하/좌우 미러링 화면 > ");
}

// 5-B.결과 이미지 시계방향으로 90도 회전
void turn90Right() {
	for (int i = 0; i < inW; i++)
		for (int k = 0; k < inH; k++)
			outImage[i][k] = inImage[inH - k - 1][i];

	printf("\t\t\t\t\t  < 시계방향 90도 회전 화면 > ");
}
// 5-B.결과 이미지 시계방향으로 180도 회전
void turn180Right() {
	for (int i = 0; i < inW; i++)
		for (int k = 0; k < inH; k++)
			outImage[i][k] = inImage[inH - i - 1][inW - k - 1];

	printf("\t\t\t\t\t  < 시계방향 180도 회전 화면 > ");
}
// 5-B.결과 이미지 시계방향으로 270도 회전
void turn270Right() {
	for (int i = 0; i < inW; i++)
		for (int k = 0; k < inH; k++)
			outImage[i][k] = inImage[k][inH - i - 1];

	printf("\t\t\t\t\t  < 시계방향 270도 회전 화면 > ");
}
// 5-B.결과 이미지 반시계방향으로 90도 회전
void turn90Left() {
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			outImage[i][k] = inImage[k][inH - 1 - i];

	printf("\t\t\t\t\t  < 반시계방향 90도 회전 화면 > ");
}
// 5-B.결과 이미지 반시계방향으로 180도 회전
void turn180Left() {
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			outImage[i][k] = inImage[inH - 1 - i][inW - k - 1];

	printf("\t\t\t\t\t  < 반시계방향 180도 회전 화면 > ");
}
// 5-B.결과 이미지 반시계방향으로 270도 회전
void turn270Left() {
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			outImage[i][k] = inImage[inH - k - 1][i];

	printf("\t\t\t\t\t  < 반시계방향 270도 회전 화면 > ");
}
// 5-B.자유회전_시계방향 (포워딩)
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

			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW))
				outImage[xd][yd] = inImage[ys][xs];
		}
	}
	printf("\t\t\t\t\t  < 자유회전 %d도 회전 화면 > ", val);
}
// 5-B.자유회전_시계방향 (백워딩+중앙회전)
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

			if ((0 <= xs && xs < inH) && (0 <= ys && ys < inW))
				outImage[xd][yd] = inImage[ys][xs];
		}
	}
	printf("\t\t\t\t\t  < 자유회전_백워딩 %d도 회전 화면 > ", val);
}

// 5-C.이미지 크기 확대 (포워딩)
void sizeUp(int val) {
	// output의 크기 결정
	outH = inH * val;					// output이 input 과 달라짐
	outW = inW * val;
	outImage = malloc2D(outH, outW);

	//*** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			outImage[i * val][k * val] = inImage[i][k];

	printf("\t\t\t\t\t  < 이미지 %d배 확대 (포워딩) 화면 > ", val);
}
// 5-C.이미지 크기 확대 (백워딩)
void backwardMappingSizeUp(int val) {
	// output의 크기 결정
	outH = inH * val;					// output이 input 과 달라짐
	outW = inW * val;
	outImage = malloc2D(outH, outW);

	//*** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			outImage[i][k] = inImage[i / val][k / val];

	printf("\t\t\t\t\t  < 이미지 %d배 확대 (백워딩) 화면 > ", val);
}
// 5-C.이미지 크기 축소 (포워딩)
void sizeDown(int val) {
	// output의 크기 결정
	outH = inH / val;					// output이 input 과 달라짐
	outW = inW / val;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			outImage[i / val][k / val] = inImage[i][k];

	printf("\t\t\t\t\t  < 이미지 %d배 축소 (포워딩) 화면 > ", val);
}
// 5-C.이미지 크기 축소 (백워딩)
void backwardMappingSizeDown(int val) {
	// output의 크기 결정
	outH = inH / val;					// output이 input 과 달라짐
	outW = inW / val;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			outImage[i][k] = inImage[i * val][k * val];

	printf("\t\t\t\t\t  < 이미지 %d배 축소 (백워딩) 화면 > ", val);
}

// 5-F.모핑 이미지 

//// ********************************************************************************* ////





