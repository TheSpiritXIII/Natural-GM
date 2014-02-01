namespace NGM
{
	namespace Resource
	{
		
		struct Serializer2
		{
			typedef void (*LayoutRequestFunc)(Model::ResourceProjectItem *item);
			typedef bool (*FileRequestFunc)(const QString &filename);
			const LayoutRequestFunc layoutCreate;
			const LayoutRequestFunc layoutLoad;
			const LayoutRequestFunc layoutSave;
			const FileRequestFunc fileAllowed;
			const FileRequestFunc fileDropped;
		}
	}
}