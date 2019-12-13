void CBiped::Read(PFILE *fp)
{
	int read_start = 1;
	int i;
	D3DMATRIX mat_temp;

	long fileSize = getFileSize(fp);
	unsigned char* stream = new unsigned char[fileSize];
	unsigned char* streamOrg = stream;
	pfread(stream, fileSize, 1, fp);

	// Half Frame인지를 읽는다..
	readData(&m_bHalfFrame, sizeof(BOOL), 1, &stream);
	// Biped 의 Object 갯수를 읽는다.
	readData(&m_BipedNum, sizeof(int), 1, &stream);

	m_AniMat = new CAniMatrix[m_BipedNum];
	// Biped 의 Animation 갯수를 읽는다.
	readData(&(m_AnimCount), sizeof(int), 1, &stream);

	for (int bi = 0; bi < m_BipedNum; bi++)
	{
		// Animation Matrix 읽기.
		int anim_count;
		if (m_bHalfFrame)
			anim_count = (m_AnimCount+1)/2;
		else
			anim_count = m_AnimCount;

		m_AniMat[bi].m_Mats = new D3DMATRIX[anim_count];
		mat_temp._14 = mat_temp._24 = mat_temp._34 = 0.0f;
		mat_temp._44 = 1.0f;
		for (i = 0; i < anim_count; i++)
		{
			readData(&(mat_temp._11), sizeof(float), 1, &stream);
			readData(&(mat_temp._12), sizeof(float), 1, &stream);
			readData(&(mat_temp._13), sizeof(float), 1, &stream);
			readData(&(mat_temp._21), sizeof(float), 1, &stream);
			readData(&(mat_temp._22), sizeof(float), 1, &stream);
			readData(&(mat_temp._23), sizeof(float), 1, &stream);
			readData(&(mat_temp._31), sizeof(float), 1, &stream);
			readData(&(mat_temp._32), sizeof(float), 1, &stream);
			readData(&(mat_temp._33), sizeof(float), 1, &stream);
			readData(&(mat_temp._41), sizeof(float), 1, &stream);
			readData(&(mat_temp._42), sizeof(float), 1, &stream);
			readData(&(mat_temp._43), sizeof(float), 1, &stream);

			memcpy(&(m_AniMat[bi].m_Mats[i]), &mat_temp, sizeof(D3DMATRIX));
		}
	}
	SAFE_DELETE_ARRAY(streamOrg);
}

int CBiped::Read( char* szFileName )
{
	if( !strlen(szFileName) )
		return VF_ERR_NULL_STRING;

	m_filename = szFileName;

	PFILE* fp = pfopen( m_filename.c_str(), "rb" );
	if( !fp )
		return VF_ERR_NULL_PT;
	Read( fp );
	pfclose( fp );
	return VF_ERR_NONE;
}
