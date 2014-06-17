#ifndef __FILTERGRAPH_JUCEHEADER__
#define __FILTERGRAPH_JUCEHEADER__

class FilterInGraph;
class FilterGraph;

const char* const filenameSuffix = ".filtergraph";
const char* const filenameWildcard = "*.filtergraph";

class FilterGraph   : public FileBasedDocument
{
public:
  
  FilterGraph (AudioPluginFormatManager& formatManager);
  ~FilterGraph();

  AudioProcessorGraph& getGraph() noexcept { return graph; }

  int getNumFilters() const noexcept;
  const AudioProcessorGraph::Node::Ptr getNode (const int index) const noexcept;
  const AudioProcessorGraph::Node::Ptr getNodeForId (const uint32 uid) const noexcept;

  uint32 addFilter (const PluginDescription* desc, double x, double y);

  void removeFilter (const uint32 filterUID);
  void disconnectFilter (const uint32 filterUID);

  void removeIllegalConnections();

  void setNodePosition (const int nodeId, double x, double y);
  void getNodePosition (const int nodeId, double& x, double& y) const;

  
  int getNumConnections() const noexcept;
  const AudioProcessorGraph::Connection* getConnection (const int index) const noexcept;

  const AudioProcessorGraph::Connection* getConnectionBetween (uint32 sourceFilterUID, int sourceFilterChannel,
      uint32 destFilterUID, int destFilterChannel) const noexcept;

  bool canConnect (uint32 sourceFilterUID, int sourceFilterChannel,
                   uint32 destFilterUID, int destFilterChannel) const noexcept;

  bool addConnection (uint32 sourceFilterUID, int sourceFilterChannel,
                      uint32 destFilterUID, int destFilterChannel);

  void removeConnection (const int index);

  void removeConnection (uint32 sourceFilterUID, int sourceFilterChannel,
                         uint32 destFilterUID, int destFilterChannel);

  void clear();

  XmlElement* createXml() const;
  void restoreFromXml (const XmlElement& xml);

  
  String getDocumentTitle();
  Result loadDocument (const File& file);
  Result saveDocument (const File& file);
  File getLastDocumentOpened();
  void setLastDocumentOpened (const File& file);

  // The special channel index used to refer to a filter's midi channel
  static const int midiChannelNumber;

private:
  
  AudioPluginFormatManager& formatManager;
  AudioProcessorGraph graph;

  uint32 lastUID;
  uint32 getNextUID() noexcept;

  void createNodeFromXml (const XmlElement& xml);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGraph)
};


#endif   // __FILTERGRAPH_JUCEHEADER__
