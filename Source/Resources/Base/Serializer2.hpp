namespace NGM
{
	namespace Resource
	{
		struct TypeIdentifier
		{
			Resource::Type *type;
			const QString name;
		};

		struct Serializer2
		{
			typedef void (*ProjectRequestFunc)(Model::ResourceProjectItem *item);
			typedef bool (*FileRequestFunc)(const QString &filename);
			typedef bool (*FileNameFunc)(const QString &oldName, Model::ResourceBaseItem *item);
			typedef bool (*FileAddFunc)(QList<TypeIdentifier> *typeList, Model::ResourceGroupItem *item);
			const ProjectRequestFunc	projectCreate;
			const ProjectRequestFunc	projectLoad;
			const ProjectRequestFunc	projectSave;
			const FileNameFunc			projectRenamed;
			const FileRequestFunc		fileAllowed;
			const FileRequestFunc		fileDropped;
			const FileRequestFunc		fileDeleted;
			const FileNameFunc			fileRenamed;
			const FileAddFunc			fileAddRequest;
		};
	}
}
