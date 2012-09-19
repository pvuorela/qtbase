/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QDOCDATABASE_H
#define QDOCDATABASE_H

#include <qstring.h>
#include <qmap.h>
#include "tree.h"

QT_BEGIN_NAMESPACE

typedef QMap<QString, DocNode*> DocNodeMap;
typedef QMap<QString, QmlClassNode*> QmlTypeMap;
typedef QMap<QString, NodeMap> NodeMapMap;
typedef QMap<QString, NodeMultiMap> NodeMultiMapMap;
typedef QMultiMap<QString, Node*> QDocMultiMap;
typedef QMap<Text, const Node*> TextToNodeMap;

class QDocDatabase
{
 public:
    static QDocDatabase* qdocDB();
    static void destroyQdocDB();
    ~QDocDatabase();

    const DocNodeMap& modules() const { return modules_; }
    const DocNodeMap& qmlModules() const { return qmlModules_; }
    DocNode* addModule(const QString& name);
    DocNode* addQmlModule(const QString& name);
    DocNode* addToModule(const QString& name, Node* node);
    DocNode* addToQmlModule(const QString& moduleName, Node* node);
    DocNode* findModule(const QString& qmlModuleName, bool addIfNotFound = false);
    DocNode* findQmlModule(const QString& name, bool addIfNotFound = false);
    QmlClassNode* findQmlType(const QString& qmid, const QString& name) const;

    void findAllClasses(const InnerNode *node);
    void findAllFunctions(const InnerNode *node);
    void findAllLegaleseTexts(const InnerNode *node);
    void findAllNamespaces(const InnerNode *node);
    void findAllSince(const InnerNode *node);
    void buildCollections();

    // special collection access functions
    NodeMap& getCppClasses() { return nonCompatClasses_; }
    NodeMap& getMainClasses() { return mainClasses_; }
    NodeMap& getCompatibilityClasses() { return compatClasses_; }
    NodeMap& getObsoleteClasses() { return obsoleteClasses_; }
    NodeMap& getNamespaces() { return namespaceIndex_; }
    NodeMap& getServiceClasses() { return serviceClasses_; }
    NodeMap& getQmlTypes() { return qmlClasses_; }
    NodeMapMap& getFunctionIndex() { return funcIndex_; }
    TextToNodeMap& getLegaleseTexts() { return legaleseTexts_; }
    const NodeMultiMap& groups() const { return tree_->groups(); }
    const NodeList getGroup(const QString& name) const { return tree_->groups().values(name); }
    void getGroup(const QString& name, NodeMap& group) const;
    const NodeMap& getClassMap(const QString& key) const;
    const NodeMap& getQmlTypeMap(const QString& key) const;
    const NodeMultiMap& getSinceMap(const QString& key) const;

    const Node* resolveTarget(const QString& target, const Node* relative, const Node* self=0);
    const Node* findNodeForTarget(const QString& target, const Node* relative, const Atom* atom=0);

    /* convenience functions
       Many of these will be either eliminated or replaced.
    */
    Tree* tree() { return tree_; }
    QString version() const { return tree_->version(); }
    NamespaceNode* treeRoot() { return tree_->root(); }
    void setVersion(const QString& version) { tree_->setVersion(version); }
    void resolveInheritance() { tree_->resolveInheritance(); }
    void readIndexes(const QStringList& indexFiles) { tree_->readIndexes(indexFiles); }
    void resolveIssues();
    void generateTagFile(const QString& name) { if (!name.isEmpty()) tree_->generateTagFile(name); }
    void addToGroup(Node* node, const QString& group) { tree_->addToGroup(node, group); }
    void addToPublicGroup(Node* node, const QString& group) { tree_->addToPublicGroup(node, group); }
    void fixInheritance() { tree_->fixInheritance(); }
    void resolveProperties() { tree_->resolveProperties(); }

    const Node* findNode(const QStringList& path) { return tree_->findNode(path); }
    ClassNode* findClassNode(const QStringList& path) { return tree_->findClassNode(path); }
    NamespaceNode* findNamespaceNode(const QStringList& path) { return tree_->findNamespaceNode(path); }

    DocNode* findGroupNode(const QStringList& path) { return tree_->findGroupNode(path); }
    NameCollisionNode* findCollisionNode(const QString& name) const {
        return tree_->findCollisionNode(name);
    }

    const DocNode* findDocNodeByTitle(const QString& title, const Node* relative=0) const {
        return tree_->findDocNodeByTitle(title, relative);
    }
    const Node* findUnambiguousTarget(const QString& target, Atom* &atom, const Node* relative) const {
        return  tree_->findUnambiguousTarget(target, atom, relative);
    }
    Atom* findTarget(const QString& target, const Node* node) const {
        return tree_->findTarget(target, node);
    }
    void generateIndex(const QString& fileName,
                       const QString& url,
                       const QString& title,
                       Generator* g,
                       bool generateInternalNodes = false) {
        tree_->generateIndex(fileName, url, title, g, generateInternalNodes);
    }
    FunctionNode* findFunctionNode(const QStringList& parentPath, const FunctionNode* clone) {
        return tree_->findFunctionNode(parentPath, clone);
    }
    Node* findNodeByNameAndType(const QStringList& path, Node::Type type, Node::SubType subtype){
        return tree_->findNodeByNameAndType(path, type, subtype, 0);
    }
    NameCollisionNode* checkForCollision(const QString& name) const {
        return tree_->checkForCollision(name);
    }
    void addBaseClass(ClassNode* subclass,
                      Node::Access access,
                      const QStringList& basePath,
                      const QString& dataTypeWithTemplateArgs,
                      InnerNode* parent) {
        tree_->addBaseClass(subclass, access, basePath, dataTypeWithTemplateArgs, parent);
    }
    void addPropertyFunction(PropertyNode* property,
                             const QString& funcName,
                             PropertyNode::FunctionRole funcRole) {
        tree_->addPropertyFunction(property, funcName, funcRole);
    }

    /* debugging functions */
    void printModules() const;
    void printQmlModules() const;

 private:
    QDocDatabase();
    QDocDatabase(QDocDatabase const& ) { };         // copy constructor is private
    QDocDatabase& operator=(QDocDatabase const& );  // assignment operator is private

 private:
    static QDocDatabase*    qdocDB_;
    QDocMultiMap            masterMap_;
    Tree*                   tree_;
    DocNodeMap              modules_;
    DocNodeMap              qmlModules_;
    QmlTypeMap              qmlTypeMap_;

    NodeMap                 nonCompatClasses_;
    NodeMap                 mainClasses_;
    NodeMap                 compatClasses_;
    NodeMap                 obsoleteClasses_;
    NodeMap                 namespaceIndex_;
    NodeMap                 serviceClasses_;
    NodeMap                 qmlClasses_;
    NodeMapMap              newClassMaps_;
    NodeMapMap              newQmlTypeMaps_;
    NodeMultiMapMap         newSinceMaps_;
    NodeMapMap              funcIndex_;
    TextToNodeMap           legaleseTexts_;
};

QT_END_NAMESPACE

#endif
