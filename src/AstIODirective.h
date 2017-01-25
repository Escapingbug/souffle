/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file AstIODirective.h
 *
 * Define the class AstIODirective to hold key=value pairs for IO.
 *
 ***********************************************************************/

#pragma once

#include "AstNode.h"
#include "AstRelationIdentifier.h"

#include <map>
#include <map>
#include <string>

namespace souffle {

/**
 * @class AstIODirective
 * @brief Intermediate representation of an argument of a Literal (e.g., a variable or a constant)
 */
class AstIODirective : public AstNode {
public:
    virtual ~AstIODirective() {}

    /** Obtains a list of all embedded child nodes */
    virtual std::vector<const AstNode*> getChildNodes() const {
        return std::vector<const AstNode*>();  // type is just cached, not essential
    }

    /** Creates a clone if this AST sub-structure */
    virtual AstIODirective* clone() const {
        auto res = new AstIODirective();
        res->name = name;
        res->kvps = kvps;
        return res;
    }

    /** No nested nodes to apply to */
    virtual void apply(const AstNodeMapper& mapper) {}

    /** Output to a given output stream */
    virtual void print(std::ostream& os) const {
        os << getName() << "(";
        bool first = true;
        for (auto& pair : kvps) {
            if (first) {
                first = false;
            } else {
                os << ',';
            }
            os << pair.first << '=' << pair.second;
        }
        os << ')';
    }

    /** Return the name of this kvp map */
    const AstRelationIdentifier& getName() const {
        return name;
    }

    /** Set kvp map name */
    void setName(const AstRelationIdentifier& n) {
        name = n;
    }

    void addKVP(const std::string& key, const std::string& value) {
        kvps[key] = value;
    }

    void setAsInput() {
        input = true;
    }
    void setAsOutput() {
        input = false;
    }

protected:
    /** An internal function to determine equality to another node */
    virtual bool equal(const AstNode& node) const {
        assert(dynamic_cast<const AstIODirective*>(&node));
        const AstIODirective& other = static_cast<const AstIODirective&>(node);
        return other.name == name && other.input == input && other.kvps == kvps;
    }

    /** Name of the kvp */
    AstRelationIdentifier name;

    /** kvp map */
    std::map<std::string, std::string> kvps;
    /** input = true, output = false */
    bool input = true;
};

}  // end of namespace souffle
